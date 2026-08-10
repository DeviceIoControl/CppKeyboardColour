// Created by DeviceIoControl

#pragma once

#include "IDevice.h"
#include "Host.h"
#include "DeviceChannelType.h"
#include "DeviceIdRetriever.h"
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
	HostFactory(std::unique_ptr<DeviceIdRetriever> pDevIdRetriever);
	HostFactory();

	~HostFactory() = default;

	std::unique_ptr<Host> Create();

private:
	uint32_t m_deviceId = 0;
	std::unique_ptr<DeviceIdRetriever> m_devIdRetriever;
	std::map<uint32_t, HOST_DEVICE_PROPS> m_deviceIdToDevProps{};
	std::unique_ptr<DeviceFactory> m_devFactory{};

	void InitializeHostDeviceProperties();

	bool InitializeDeviceFactory();

	std::vector<std::shared_ptr<IDevice>> CreateRequiredDevices(DeviceMask deviceTypes);
	
	KeyboardType GetKeyboardType(uint32_t deviceId) const;

	DeviceChannelType GetDeviceChannelType(uint32_t deviceId) const;

	DeviceMask GetHostDevices(uint32_t deviceId) const;

	void InitializeSingleZoneKBs();

	void InitializeTripleZoneKBs();

	void InitializeTripleZoneKBsWithPeripherals();
};