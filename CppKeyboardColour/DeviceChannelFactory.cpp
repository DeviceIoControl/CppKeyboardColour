// Created by DeviceIoControl

#include "stdafx.h"
#include "DeviceChannelFactory.h"
#include "DeviceChannel.h"

#include "WmiDeviceChannel.h"
#include "InsydeDeviceChannel.h"
#include "DebugDeviceChannel.h"

DeviceChannelFactory::DeviceChannelFactory(bool enableChannelMonitoring)
	: m_pDbgChannel(std::make_shared<DebugDeviceChannel>()),
	m_enableChannelMonitoring(enableChannelMonitoring)
{
}

std::shared_ptr<IDeviceChannel> DeviceChannelFactory::Create(DeviceChannelType channelType) const
{
	switch (channelType)
	{
	case DeviceChannelType::Debug:
		return m_pDbgChannel;

	case DeviceChannelType::Wmi:
		return std::make_shared<DeviceChannel>(std::make_shared<WmiDeviceChannel>(), m_enableChannelMonitoring ? m_pDbgChannel : nullptr);
		
	case DeviceChannelType::Insyde:
		return std::make_shared<DeviceChannel>(std::make_shared<InsydeDeviceChannel>(), m_enableChannelMonitoring ? m_pDbgChannel : nullptr);
	}

	return nullptr;
}
