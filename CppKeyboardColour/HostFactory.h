// Created by DeviceIoControl

#pragma once

#include "IDevice.h"
#include "Host.h"
#include "DeviceFactory.h"
#include "ModelIdentifier.h"

class HostFactory 
{
public:
	HostFactory(std::unique_ptr<ModelIdentifier> pModelId, bool enableDeviceMonitoring);
	HostFactory(bool useDbgChannel = false, bool enableDeviceMonitoring = false);

	std::unique_ptr<Host> Create();

	~HostFactory() = default;

private:
	bool m_enableDeviceMonitoring = false;
	std::unique_ptr<DeviceFactory> m_devFactory;
	std::shared_ptr<ModelIdentifier> m_modelIdentifer;

	std::vector<std::shared_ptr<IDevice>> CreateRequiredDevices(DeviceMask deviceTypes);
};