// Created by DeviceIoControl

#include "stdafx.h"
#include "HostFactory.h"
#include "DeviceChannelFactory.h"
#include "LegacyModelIdRetriever.h"
#include "ModelIdRetriever.h"

HostFactory::HostFactory(std::unique_ptr<IModelIdRetriever> pModelIdRetriever, std::unique_ptr<ModelIdTranslator> pModelIdTranslator, bool enableDeviceMonitoring)
	: m_modelIdTranslator(std::move(pModelIdTranslator)),
	m_enableDeviceMonitoring(enableDeviceMonitoring)
{
	m_modelId = pModelIdRetriever->GetModelID();
	m_modelIdTranslator = std::make_shared<ModelIdTranslator>(std::move(pModelIdRetriever));

	DeviceChannelFactory devChannelFactory(m_modelIdTranslator->GetKeyboardType(), enableDeviceMonitoring);
	m_devFactory = std::make_unique<DeviceFactory>(devChannelFactory.Create(m_modelIdTranslator->GetDeviceChannelType()));
}

HostFactory::HostFactory(std::unique_ptr<IModelIdRetriever> pModelIdRetriever, bool enableDeviceMonitoring)
	: m_enableDeviceMonitoring(enableDeviceMonitoring)
{
	m_modelId = pModelIdRetriever->GetModelID();
	m_modelIdTranslator = std::make_shared<ModelIdTranslator>(std::move(pModelIdRetriever));

	DeviceChannelFactory devChannelFactory(m_modelIdTranslator->GetKeyboardType(), enableDeviceMonitoring);
	m_devFactory = std::make_unique<DeviceFactory>(devChannelFactory.Create(m_modelIdTranslator->GetDeviceChannelType()));
}

HostFactory::HostFactory(bool useDbgChannel /*= false*/, bool enableDeviceMonitoring /*= false*/)
	: HostFactory(std::make_unique<ModelIdRetriever>(useDbgChannel), enableDeviceMonitoring)
{
}

std::unique_ptr<Host> HostFactory::Create()
{
	std::printf("Detected Model ID: 0x%08x\n", m_modelId);

	const auto hostDevices = m_modelIdTranslator->GetHostDevices();
	if (hostDevices == DeviceMask::Unknown)
	{
		return nullptr;
	}

	const auto devices = this->CreateRequiredDevices(hostDevices);
	return std::make_unique<Host>(m_modelId, m_modelIdTranslator->GetModelName(), devices);
}

std::vector<std::shared_ptr<IDevice>> HostFactory::CreateRequiredDevices(DeviceMask deviceTypes)
{
	std::vector<std::shared_ptr<IDevice>> devices{};

	if (!!(deviceTypes & DeviceMask::Keyboard))
	{
		const auto keyboardType = m_modelIdTranslator->GetKeyboardType();
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
