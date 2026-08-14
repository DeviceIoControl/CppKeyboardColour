// Created by DeviceIoControl

#include "stdafx.h"
#include "DeviceChannel.h"

DeviceChannel::DeviceChannel(std::shared_ptr<IDeviceChannel> pUnderlyingDevChannel, std::shared_ptr<IDeviceChannel> pDbgChannel)
	: m_pDevChannel(std::move(pUnderlyingDevChannel)),
	m_pDbgChannel(std::move(pDbgChannel))
{
}

bool DeviceChannel::SendCode(uint32_t code) 
{
	if (m_pDbgChannel)
	{
		m_pDbgChannel->SendCode(code);
	}

	return m_pDevChannel->SendCode(code);
}

DeviceChannelType DeviceChannel::QueryType() const 
{
	return m_pDevChannel->QueryType();
}