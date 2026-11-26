// Created by DeviceIoControl

#pragma once
#include "IModelIdRetriever.h"

namespace Detail 
{
	using T_GetProductID_PCI = DWORD(*__stdcall)();
} // namespace Detail

class LegacyModelIdRetriever
	: public IModelIdRetriever
{
public:
	explicit LegacyModelIdRetriever(bool useDebugModel = false);

	uint32_t GetModelID() override;

	~LegacyModelIdRetriever() override;

private:
	bool m_useDebugModel = false;
	HMODULE m_hGetProductDLL = nullptr;
	Detail::T_GetProductID_PCI m_pfnGetProductID = nullptr;
};