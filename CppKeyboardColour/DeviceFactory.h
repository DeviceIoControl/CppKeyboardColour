// Created by DeviceIoControl

#pragma once

#include "IDevice.h"
#include "IDeviceChannel.h"
#include "KeyboardType.h"

class DeviceFactory 
{
public:
	DeviceFactory(std::shared_ptr<IDeviceChannel> pDevChannel);

	std::unique_ptr<IDevice> CreateKeyboard(KeyboardType kbType);

	std::unique_ptr<IDevice> CreateLightbar();

	std::unique_ptr<IDevice> CreateLogo();

	~DeviceFactory() = default;	

private:
	std::shared_ptr<IDeviceChannel> m_pDevChannel;
};
