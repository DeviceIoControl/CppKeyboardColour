// Created by DeviceIoControl

#include "stdafx.h"
#include "DeviceFactory.h"
#include "../Devices/LogoDevice.h"
#include "../Devices/KeyboardDevice.h"
#include "../Devices/LightbarDevice.h"
#include "../Channels/DeviceChannelFactory.h"

DeviceFactory::DeviceFactory(std::shared_ptr<ModelIdentifier> pDevModelId, bool enableDeviceMonitorMode)
	: m_pModelIdentifier(std::move(pDevModelId))
{
	DeviceChannelFactory devChannelFactory(m_pModelIdentifier->GetKeyboardType(), enableDeviceMonitorMode);
	m_pDevChannel = devChannelFactory.Create(m_pModelIdentifier->GetDeviceChannelType());
}

std::unique_ptr<IDevice> DeviceFactory::CreateKeyboard()
{
	return std::make_unique<KeyboardDevice>(m_pModelIdentifier->GetKeyboardType(), m_pDevChannel);
}

std::unique_ptr<IDevice> DeviceFactory::CreateLightbar()
{
	return std::make_unique<LightbarDevice>(m_pDevChannel);
}

std::unique_ptr<IDevice> DeviceFactory::CreateLogo()
{
	return std::make_unique<LogoDevice>(m_pDevChannel);
}
