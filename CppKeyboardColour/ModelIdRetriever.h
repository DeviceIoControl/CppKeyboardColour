// Created by DeviceIoControl

#pragma once
#include "WbemService.h"
#include "IModelIdRetriever.h"

class ModelIdRetriever 
	: public IModelIdRetriever
{
public:
	ModelIdRetriever(bool useDebugModel = false);
	~ModelIdRetriever() override = default;

	uint32_t GetModelID() override;

private:
	bool m_useDbgModelId = false;
	WbemService m_wbemService{ L"ROOT\\CIMV2" };
};

