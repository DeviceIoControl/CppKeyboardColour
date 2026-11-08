// Created by DeviceIoControl

#pragma once

#include "Host.h"
#include "Devices/IDevice.h"
#include "Devices/DeviceFactory.h"
#include "Identifier/ModelIdentifier.h"

//
// EnableDebugMode = Compile in Debug mode to enable this. 
//
// - This enables debug logging and the program will run on all devices.
// We will always return MODEL_ID_DEBUG and won't compare against the supported device list.
//
// EnableDeviceMonitorMode = Compile in TestBuild (or provide "--dmm" argument) to enable this.
// 
// - This enables debug logging, but the program will only run on supported devices.
// We will attempt to retrieve the real Model ID and will compare it against the supported device list.
//
enum HostFactoryFlags : uint16_t
{
	None = 0,
	EnableDebugMode = 1,
	EnableDeviceMonitorMode = 2
};

class HostFactory
{
public:
	HostFactory(std::unique_ptr<ModelIdentifier> pModelId, HostFactoryFlags flags);

	std::unique_ptr<Host> Create();

	~HostFactory() = default;

private:
	std::unique_ptr<DeviceFactory> m_devFactory;
	std::shared_ptr<ModelIdentifier> m_modelIdentifer;

	std::vector<std::shared_ptr<IDevice>> CreateRequiredDevices(DeviceMask deviceTypes);
};