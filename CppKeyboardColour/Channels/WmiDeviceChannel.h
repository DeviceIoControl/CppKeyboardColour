// Created by DeviceIoControl

#pragma once

#include "IDeviceChannel.h"
#include "../Utils/WbemService.h"
#include "../Utils/ScopedComPtr.h"

class WmiDeviceChannel
	: public IDeviceChannel
{
public:
	WmiDeviceChannel();
	~WmiDeviceChannel() = default;

	bool SendCode(uint32_t code) override;
	DeviceChannelType QueryType() const;

private:
	WbemService m_wbemService{};
	ScopedComPtr<IWbemClassObject> m_pDataParameter;
	ScopedComPtr<IWbemClassObject> m_pClevoGetObject;
};