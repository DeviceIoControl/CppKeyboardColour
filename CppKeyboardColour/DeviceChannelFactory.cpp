// Created by DeviceIoControl

#include "stdafx.h"
#include "DeviceChannelFactory.h"

#include "WmiDeviceChannel.h"
#include "InsydeDeviceChannel.h"
#include "DebugDeviceChannel.h"

DeviceChannelFactory::DeviceChannelFactory(bool enableDebugging)
	: m_pDbgChannel(enableDebugging ? std::make_shared<DebugDeviceChannel>() : nullptr)
{
}

std::shared_ptr<IDeviceChannel> DeviceChannelFactory::Create(DeviceChannelType channelType) const
{
	switch (channelType)
	{
	case DeviceChannelType::Debug:
		return m_pDbgChannel;

	case DeviceChannelType::Wmi:
		return std::make_shared<WmiDeviceChannel>(m_pDbgChannel);

	case DeviceChannelType::Insyde:
		return std::make_shared<InsydeDeviceChannel>(m_pDbgChannel);
	}

	return nullptr;
}
