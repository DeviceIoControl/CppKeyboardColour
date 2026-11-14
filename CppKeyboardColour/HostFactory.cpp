// Created by DeviceIoControl

#include "stdafx.h"
#include "HostFactory.h"
#include "Console/Logger.h"

HostFactory::HostFactory(std::unique_ptr<ModelIdentifier> pModelId, HostFactoryFlags flags)
	: m_modelIdentifer(std::move(pModelId))
{
	m_devFactory = std::make_unique<DeviceFactory>(m_modelIdentifer, !!(flags & HostFactoryFlags::EnableDeviceMonitorMode));
}

std::unique_ptr<Host> HostFactory::Create()
{
	const auto hostDevices = m_modelIdentifer->GetHostDevices();
	if (hostDevices == DeviceMask::Unknown)
	{
		KB_ERROR(L"Failed to detect the host's RGB devices.");
		return nullptr;
	}

	const auto devices = this->CreateRequiredDevices(hostDevices);
	return std::make_unique<Host>(m_modelIdentifer, devices);
}

std::vector<std::shared_ptr<IDevice>> HostFactory::CreateRequiredDevices(DeviceMask deviceTypes)
{
	std::vector<std::shared_ptr<IDevice>> devices{};

	if (!!(deviceTypes & DeviceMask::Keyboard))
	{
		devices.emplace_back(m_devFactory->CreateKeyboard());
	}

	if (!!(deviceTypes & DeviceMask::Lightbar))
	{
		devices.emplace_back(m_devFactory->CreateLightbar());
	}

	if (!!(deviceTypes & DeviceMask::Logo))
	{
		devices.emplace_back(m_devFactory->CreateLogo());
	}

	return devices;
}