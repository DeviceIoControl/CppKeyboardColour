// Created by DeviceIoControl

#include "stdafx.h"
#include "ModelIdRetriever.h"
#include "ModelIds.h"

#define GET_PRODUCT_DLL L"GetProductID64.dll"

ModelIdRetriever::ModelIdRetriever(bool fakeDevice /*= false*/) 
	: m_useFakeDevice(fakeDevice)
{
	m_hGetProductDLL = LoadGetProductDLL();
	m_pfnGetProductID = reinterpret_cast<Detail::T_GetProductID_PCI>(GetProcAddress(m_hGetProductDLL, "GetProductID_PCI"));
}

uint32_t ModelIdRetriever::GetModelID() const
{
	if (m_pfnGetProductID && !m_useFakeDevice)
	{
		// Call this function on a seperate thread to avoid causing COM issues on our thread
		// as this DLL (GetProductID64!GetProductID_PCI specifically) is buggy.
		return std::async(std::launch::async, DoGetProductID, m_pfnGetProductID).get();
	}

	return m_useFakeDevice ? MODEL_ID_FAKE : 0xFFFFFFFF;
}

ModelIdRetriever::~ModelIdRetriever()
{
	m_pfnGetProductID = nullptr;
	FreeLibrary(m_hGetProductDLL);
}

/* static */ uint32_t ModelIdRetriever::DoGetProductID(const Detail::T_GetProductID_PCI& fnGetProductID)
{
	std::ignore = CoInitializeEx(nullptr, COINIT::COINIT_APARTMENTTHREADED);
	std::ignore = CoInitializeEx(nullptr, COINIT::COINIT_APARTMENTTHREADED);

	return fnGetProductID();
}

HMODULE ModelIdRetriever::LoadGetProductDLL() const
{
	auto const hModule = LoadLibraryW(GET_PRODUCT_DLL);

	if (!hModule || hModule == INVALID_HANDLE_VALUE)
	{
		std::wcout << L"Cannot load " << GET_PRODUCT_DLL << L". Please ensure the DLL is within the same directory!\n";
		std::exit(STATUS_DLL_NOT_FOUND);
	}

	return hModule;
}
