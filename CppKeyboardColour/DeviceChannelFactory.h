// Created by DeviceIoControl
#pragma once

#include "IDeviceChannel.h"

class DeviceChannelFactory
{
public:
	DeviceChannelFactory() = default;
	~DeviceChannelFactory() = default;

	std::shared_ptr<IDeviceChannel> Create(DeviceChannelType channelType) const;
};