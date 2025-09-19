// Created by DeviceIoControl

#include "stdafx.h"
#include "DeviceIdRetriever.h"

DeviceIdRetriever::DeviceIdRetriever()
{
	m_hGetProductDLL = LoadGetProductDLL();
	m_pfnGetProductID = reinterpret_cast<Detail::T_GetProductID_PCI>(GetProcAddress(m_hGetProductDLL, "GetProductID_PCI"));
}

uint32_t DeviceIdRetriever::GetDeviceID() const
{
	if (m_pfnGetProductID)
	{
		// Call this function on a seperate thread to avoid causing COM issues on our thread
		// as this DLL (GetProductID64!GetProductID_PCI specifically) is buggy.
		return std::async(std::launch::async, DoGetProductID, m_pfnGetProductID).get();
	}

	return 0xFFFFFFFF;
}

DeviceIdRetriever::~DeviceIdRetriever()
{
	m_pfnGetProductID = nullptr;
	FreeLibrary(m_hGetProductDLL);
}

/* static */ uint32_t DeviceIdRetriever::DoGetProductID(const Detail::T_GetProductID_PCI& fnGetProductID)
{
	CoInitializeEx(nullptr, COINIT::COINIT_APARTMENTTHREADED);
	CoInitializeEx(nullptr, COINIT::COINIT_APARTMENTTHREADED);

	return fnGetProductID();
}

HMODULE DeviceIdRetriever::LoadGetProductDLL() const
{
	auto const hModule = LoadLibraryW(GET_PRODUCT_DLL);

	if (!hModule || hModule == INVALID_HANDLE_VALUE)
	{
		std::wcout << L"Cannot load " << GET_PRODUCT_DLL << L". Please ensure the DLL is within the same directory!\n";
		std::exit(STATUS_DLL_NOT_FOUND);
	}

	return hModule;
}
