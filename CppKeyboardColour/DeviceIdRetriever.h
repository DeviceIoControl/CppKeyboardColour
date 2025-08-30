#pragma once

// Created by DeviceIoControl

#include "stdafx.h"

#define GET_PRODUCT_DLL L"GetProductID64.dll"

namespace Detail 
{
	using T_GetProductID_PCI = DWORD(*__stdcall)();
} // namespace Detail

class DeviceIdRetriever
{
public:
	DeviceIdRetriever() 
	{
		m_hGetProductDLL = LoadGetProductDLL();
		m_pfnGetProductID = reinterpret_cast<Detail::T_GetProductID_PCI>(GetProcAddress(m_hGetProductDLL, "GetProductID_PCI"));
	}

	uint32_t GetDeviceID() const
	{
		if (m_pfnGetProductID) 
		{ 
			// Call this function on a seperate thread to avoid causing COM issues on our thread
			// as this DLL (GetProductID64!GetProductID_PCI specifically) is buggy.
			return std::async(std::launch::async, DoGetProductID, m_pfnGetProductID).get();
		}

		return 0xFFFFFFFF;
	}

	~DeviceIdRetriever() 
	{
		m_pfnGetProductID = nullptr;
		FreeLibrary(m_hGetProductDLL);
	}

private:
	HMODULE m_hGetProductDLL = nullptr;
	Detail::T_GetProductID_PCI m_pfnGetProductID = nullptr;

	// NOTE: GetProductID64 (A.K.A GetProductdll.dll) is buggy and unintializes COM multiples times,
	// even though only one call to CoInitialize succeeds.
	static uint32_t DoGetProductID(const Detail::T_GetProductID_PCI& fnGetProductID) 
	{
		CoInitializeEx(nullptr, COINIT::COINIT_APARTMENTTHREADED);
		CoInitializeEx(nullptr, COINIT::COINIT_APARTMENTTHREADED);

		return fnGetProductID();
	}

	HMODULE LoadGetProductDLL()
	{
		auto const hModule = LoadLibraryW(GET_PRODUCT_DLL);

		if (!hModule || hModule == INVALID_HANDLE_VALUE)
		{
			std::wcout << L"Cannot load " << GET_PRODUCT_DLL << L". Please ensure the DLL is within the same directory!\n";
			std::exit(STATUS_DLL_NOT_FOUND);
		}

		return hModule;
	}
};