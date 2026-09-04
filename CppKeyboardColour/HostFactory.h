// Created by DeviceIoControl

#pragma once

#include "IDevice.h"
#include "Host.h"
#include "DeviceFactory.h"
#include "ModelIdTranslator.h"
#include "IModelIdRetriever.h"

class HostFactory 
{
public:
	HostFactory(std::unique_ptr<IModelIdRetriever> pModelIdRetriever, std::unique_ptr<ModelIdTranslator> pTranslator, bool enableDeviceMonitoring);
	HostFactory(bool useDbgChannel = false, bool enableDeviceMonitoring = false);

	std::unique_ptr<Host> Create();

	~HostFactory() = default;

private:
	uint32_t m_modelId = 0;
	bool m_enableDeviceMonitoring = false;
	std::unique_ptr<IModelIdRetriever> m_modelIdRetriever;
	std::unique_ptr<ModelIdTranslator> m_modelIdTranslator;
	std::unique_ptr<DeviceFactory> m_devFactory;

	void InitializeModelID();
	bool InitializeDeviceFactory();

	std::vector<std::shared_ptr<IDevice>> CreateRequiredDevices(DeviceMask deviceTypes);
};