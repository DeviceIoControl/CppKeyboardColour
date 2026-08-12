// Created by DeviceIoControl

#pragma once
#include "IDeviceChannel.h"

class DeviceChannelFactory
{
public:
	DeviceChannelFactory(bool enableDebugging);
	~DeviceChannelFactory() = default;

	std::shared_ptr<IDeviceChannel> Create(DeviceChannelType channelType) const;

private:
	std::shared_ptr<IDeviceChannel> m_pDbgChannel;
};