// Created by DeviceIoControl

#include "stdafx.h"
#include "HostFactory.h"
#include "DeviceChannelFactory.h"
#include "LegacyModelIdRetriever.h"
#include "ModelIdRetriever.h"

namespace
{
	std::ostream& operator<<(std::ostream& _Ostr, DeviceMask devices)
	{
		if (!!(devices & DeviceMask::Keyboard))
		{
			_Ostr << "[Keyboard] ";
		}

		if (!!(devices & DeviceMask::Lightbar))
		{
			_Ostr << "[Lightbar] ";
		}

		if (!!(devices & DeviceMask::Logo))
		{
			_Ostr << "[Logo] ";
		}

		return _Ostr;
	}

	std::ostream& operator<<(std::ostream& _Ostr, KeyboardType kbType)
	{
		switch (kbType)
		{
		case KeyboardType::SINGLE_ZONE:
			return _Ostr << "Single Zone";

		case KeyboardType::TRIPLE_ZONE:
			return _Ostr << "Triple Zone";

		case KeyboardType::PER_KEY:
			return _Ostr << "Per-Key";
		}

		return _Ostr;
	}

} // namespace

HostFactory::HostFactory(std::unique_ptr<IModelIdRetriever> pModelIdRetriever, std::unique_ptr<ModelIdTranslator> pModelIdTranslator, bool enableDeviceMonitoring)
	: m_modelIdRetriever(std::move(pModelIdRetriever)),
	m_modelIdTranslator(std::move(pModelIdTranslator)),
	m_enableDeviceMonitoring(enableDeviceMonitoring)
{
	this->InitializeModelID();
	this->InitializeDeviceFactory();
}

HostFactory::HostFactory(bool useDbgChannel /*= false*/, bool enableDeviceMonitoring /*= false*/)
	: HostFactory(std::make_unique<ModelIdRetriever>(useDbgChannel), std::make_unique<ModelIdTranslator>(), enableDeviceMonitoring)
{
}

std::unique_ptr<Host> HostFactory::Create()
{
	std::cout << "Detected Model ID: 0x" << (void*)m_modelId << "\n";

	const auto hostDevices = m_modelIdTranslator->GetHostDevices(m_modelId);
	if (hostDevices == DeviceMask::Unknown)
	{
		return nullptr;
	}

	std::cout << "Host Devices: " << hostDevices << "\n";
	if (!!(hostDevices & DeviceMask::Keyboard))
	{
		std::cout << "Keyboard Type: " << m_modelIdTranslator->GetKeyboardType(m_modelId) << "\n\n";
	}

	const auto devices = this->CreateRequiredDevices(hostDevices);
	return std::make_unique<Host>(m_modelId, devices);
}

void HostFactory::InitializeModelID()
{
	m_modelId = m_modelIdRetriever->GetModelID();
}

bool HostFactory::InitializeDeviceFactory()
{
	DeviceChannelFactory const devChannelFactory(m_modelIdTranslator->GetKeyboardType(m_modelId), m_enableDeviceMonitoring);

	if (const auto pDeviceChannel = devChannelFactory.Create(m_modelIdTranslator->GetDeviceChannelType(m_modelId)))
	{
		m_devFactory = std::make_unique<DeviceFactory>(pDeviceChannel);
	}

	if (m_enableDeviceMonitoring)
	{
		std::cout << "WARNING: Device monitor mode enabled! (Performance may be affected)\n\n";
	}

	return (m_modelId && m_devFactory);
}

std::vector<std::shared_ptr<IDevice>> HostFactory::CreateRequiredDevices(DeviceMask deviceTypes)
{
	std::vector<std::shared_ptr<IDevice>> devices{};

	if (!!(deviceTypes & DeviceMask::Keyboard))
	{
		const auto keyboardType = m_modelIdTranslator->GetKeyboardType(m_modelId);
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
