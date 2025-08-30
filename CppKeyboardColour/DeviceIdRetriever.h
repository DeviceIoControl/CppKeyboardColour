#pragma once

// Created by DeviceIoControl

#include "stdafx.h"

#define GET_PRODUCT_DLL L"GetProductID64.dll"

namespace Detail 
{
	using T_GetProductID = DWORD(*__stdcall)();
} // namespace Detail

class DeviceIdRetriever
{
public:
	DeviceIdRetriever() 
	{
		m_hGetProductDLL = LoadGetProductDLL();
		m_pfnGetProductID = reinterpret_cast<Detail::T_GetProductID>(GetProcAddress(m_hGetProductDLL, "GetProductID"));
	}

	uint32_t GetDeviceID() const
	{
		return m_pfnGetProductID ? m_pfnGetProductID() : 0xFFFFFFFF;
	}

	~DeviceIdRetriever() 
	{
		m_pfnGetProductID = nullptr;
		FreeLibrary(m_hGetProductDLL);
	}

private:
	HMODULE m_hGetProductDLL = nullptr;
	Detail::T_GetProductID m_pfnGetProductID = nullptr;

	HMODULE LoadGetProductDLL()
	{
		return LoadLibraryW(GET_PRODUCT_DLL);
	}
};