// Created by DeviceIoControl

#pragma once

#include "ScopedComPtr.h"
#include "IDeviceChannel.h"
#include "WbemService.h"

class WmiDeviceChannel
	: public IDeviceChannel
{
public:
	WmiDeviceChannel(std::shared_ptr<IDeviceChannel> pDbgChannel);
	~WmiDeviceChannel() = default;

	bool SendCode(uint32_t code) override;
	DeviceChannelType QueryType() const;

private:
	WbemService m_wbemService{};
	std::shared_ptr<IDeviceChannel> m_pDbgChannel{};
	ScopedComPtr<IWbemClassObject> m_pDataParameter;
	ScopedComPtr<IWbemClassObject> m_pClevoGetObject;
};