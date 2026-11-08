// Created by DeviceIoControl

#pragma once

#include "IDevice.h"
#include "../Common/KeyboardType.h"
#include "../Channels/IDeviceChannel.h"
#include "../Identifier/ModelIdentifier.h"

class DeviceFactory
{
public:
	DeviceFactory(std::shared_ptr<ModelIdentifier> pDevModelId, bool enableDeviceMonitorMode);
	
	std::unique_ptr<IDevice> CreateKeyboard();
	std::unique_ptr<IDevice> CreateLightbar();
	std::unique_ptr<IDevice> CreateLogo();

	~DeviceFactory() = default;	

private:
	std::shared_ptr<IDeviceChannel> m_pDevChannel;
	std::shared_ptr<ModelIdentifier> m_pModelIdentifier;
};
