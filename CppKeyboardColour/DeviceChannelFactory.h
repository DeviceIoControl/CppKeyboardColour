// Created by DeviceIoControl

#pragma once
#include "IDeviceChannel.h"
#include "KeyboardType.h"

class DeviceChannelFactory
{
public:
	DeviceChannelFactory(KeyboardType kbType, bool enableChannelMonitoring);
	~DeviceChannelFactory() = default;

	std::shared_ptr<IDeviceChannel> Create(DeviceChannelType channelType) const;

private:
	bool m_enableChannelMonitoring = false;
	std::shared_ptr<IDeviceChannel> m_pDbgChannel;
};