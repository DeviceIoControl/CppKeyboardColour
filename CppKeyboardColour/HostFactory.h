// Created by DeviceIoControl

#pragma once

#include "IDevice.h"
#include "Host.h"
#include "DeviceChannelType.h"
#include "ModelIdRetriever.h"
#include "DeviceFactory.h"

struct HOST_DEVICE_PROPS
{
	KeyboardType kbType;
	DeviceMask devices;
	DeviceChannelType deviceChannelType;
};

class HostFactory 
{
public:
	HostFactory(std::unique_ptr<ModelIdRetriever> pModelIdRetriever);
	HostFactory(bool useFakeDevice = false);

	~HostFactory() = default;

	std::unique_ptr<Host> Create();

private:
	uint32_t m_modelId = 0;
	std::unique_ptr<ModelIdRetriever> m_modelIdRetriever;
	std::map<uint32_t, HOST_DEVICE_PROPS> m_modelIdToDevProps{};
	std::unique_ptr<DeviceFactory> m_devFactory{};

	void InitializeHostDeviceProperties();

	bool InitializeDeviceFactory();

	std::vector<std::shared_ptr<IDevice>> CreateRequiredDevices(DeviceMask deviceTypes);
	
	KeyboardType GetKeyboardType(uint32_t modelId) const;

	DeviceChannelType GetDeviceChannelType(uint32_t modelId) const;

	DeviceMask GetHostDevices(uint32_t modelId) const;

	void InitializeSingleZoneKBs();

	void InitializeTripleZoneKBs();

	void InitializeTripleZoneKBsWithPeripherals();
};