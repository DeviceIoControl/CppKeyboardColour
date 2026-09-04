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

	std::wstring GetPnpDeviceId(IWbemClassObject* pObject);
	bool IsPCIDeviceInstancePath(const std::wstring& devInstPath);
	std::wstring ExtractDeviceInstancePathSubsystem(const std::wstring& devInstPath);
	uint32_t ExtractSubsystemID(const std::wstring& subsystem);
};

