// Created by DeviceIoControl

#include "stdafx.h"
#include "HostFactory.h"
#include "DeviceChannelFactory.h"

HostFactory::HostFactory(std::unique_ptr<ModelIdentifier> pModelId, bool enableDeviceMonitoring)
	: m_modelIdentifer(std::move(pModelId)),
	m_enableDeviceMonitoring(enableDeviceMonitoring)
{
	DeviceChannelFactory devChannelFactory(m_modelIdentifer->GetKeyboardType(), enableDeviceMonitoring);
	m_devFactory = std::make_unique<DeviceFactory>(devChannelFactory.Create(m_modelIdentifer->GetDeviceChannelType()));
}

HostFactory::HostFactory(bool useDbgChannel /*= false*/, bool enableDeviceMonitoring /*= false*/)
	: HostFactory(std::make_unique<ModelIdentifier>(USE_LEGACY_MODEL_RETRIEVER, useDbgChannel), enableDeviceMonitoring)
{
}

std::unique_ptr<Host> HostFactory::Create()
{
	std::printf("Detected Model ID: 0x%08x\n", m_modelIdentifer->GetModelID());

	const auto hostDevices = m_modelIdentifer->GetHostDevices();
	if (hostDevices == DeviceMask::Unknown)
	{
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
		const auto keyboardType = m_modelIdentifer->GetKeyboardType();
		devices.emplace_back(m_devFactory->CreateKeyboard(keyboardType));
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
