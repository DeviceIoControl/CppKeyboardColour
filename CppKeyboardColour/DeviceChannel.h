// Created by DeviceIoControl

#pragma once
#include "IDeviceChannel.h"

class DeviceChannel 
	: public IDeviceChannel
{
public:
	DeviceChannel(std::shared_ptr<IDeviceChannel> pUnderlyingDevChannel, std::shared_ptr<IDeviceChannel> pDbgChannel);
	~DeviceChannel() override = default;

	bool SendCode(uint32_t code) override;
	DeviceChannelType QueryType() const override;

private:
	std::shared_ptr<IDeviceChannel> m_pDevChannel;
	std::shared_ptr<IDeviceChannel> m_pDbgChannel;
};