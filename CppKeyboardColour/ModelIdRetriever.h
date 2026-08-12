// Created by DeviceIoControl

#pragma once

namespace Detail 
{
	using T_GetProductID_PCI = DWORD(*__stdcall)();
} // namespace Detail

class ModelIdRetriever
{
public:
	ModelIdRetriever(bool useDebugModel = false);

	uint32_t GetModelID() const;

	~ModelIdRetriever();

private:
	bool m_useDebugModel = false;
	HMODULE m_hGetProductDLL = nullptr;
	Detail::T_GetProductID_PCI m_pfnGetProductID = nullptr;

	// NOTE: GetProductID64 (A.K.A GetProductdll.dll) is buggy and unintializes COM multiples times,
	// even though only one call to CoInitialize succeeds.
	static uint32_t DoGetProductID(const Detail::T_GetProductID_PCI& fnGetProductID);

	HMODULE LoadGetProductDLL() const;
};