// Created by DeviceIoControl

#include "stdafx.h"
#include "DeviceFactory.h"
#include "KeyboardDevice.h"
#include "LightbarDevice.h"
#include "LogoDevice.h"

DeviceFactory::DeviceFactory(std::shared_ptr<IDeviceChannel> pDevChannel)
	: m_pDevChannel(std::move(pDevChannel))
{
}

std::unique_ptr<IDevice> DeviceFactory::CreateKeyboard(KeyboardType kbType)
{
	return std::make_unique<KeyboardDevice>(kbType, m_pDevChannel);
}

std::unique_ptr<IDevice> DeviceFactory::CreateLightbar()
{
	return std::make_unique<LightbarDevice>(m_pDevChannel);
}

std::unique_ptr<IDevice> DeviceFactory::CreateLogo()
{
	return std::make_unique<LogoDevice>(m_pDevChannel);
}
