// Created by DeviceIoControl

#include "stdafx.h"
#include "DeviceChannelFactory.h"

#include "WmiDeviceChannel.h"
#include "InsydeDeviceChannel.h"
#include "FakeDeviceChannel.h"

std::shared_ptr<IDeviceChannel> DeviceChannelFactory::Create(DeviceChannelType channelType) const
{
	switch (channelType)
	{
	case DeviceChannelType::Fake:
		return std::make_shared<FakeDeviceChannel>();

	case DeviceChannelType::Wmi:
		return std::make_shared<WmiDeviceChannel>();

	case DeviceChannelType::Insyde:
		return std::make_shared<InsydeDeviceChannel>();
	}

	return nullptr;
}
