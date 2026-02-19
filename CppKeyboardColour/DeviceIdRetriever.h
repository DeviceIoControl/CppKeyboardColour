#pragma once

// Created by DeviceIoControl

#define GET_PRODUCT_DLL L"GetProductID64.dll"

namespace Detail 
{
	using T_GetProductID_PCI = DWORD(*__stdcall)();
} // namespace Detail

class DeviceIdRetriever
{
public:
	DeviceIdRetriever(bool useFakeDeviceId = false);

	uint32_t GetDeviceID() const;

	~DeviceIdRetriever();

private:
	bool m_useFakeDeviceId = false;
	HMODULE m_hGetProductDLL = nullptr;
	Detail::T_GetProductID_PCI m_pfnGetProductID = nullptr;

	// NOTE: GetProductID64 (A.K.A GetProductdll.dll) is buggy and unintializes COM multiples times,
	// even though only one call to CoInitialize succeeds.
	static uint32_t DoGetProductID(const Detail::T_GetProductID_PCI& fnGetProductID);

	HMODULE LoadGetProductDLL() const;
};