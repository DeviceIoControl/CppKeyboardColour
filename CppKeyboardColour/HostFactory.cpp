// Created by DeviceIoControl

#include "stdafx.h"
#include "HostFactory.h"
#include "DeviceIds.h"
#include "DeviceChannelFactory.h"

HostFactory::HostFactory(std::unique_ptr<DeviceIdRetriever> pDevIdRetriever)
	: m_devIdRetriever(std::move(pDevIdRetriever))
{
	this->InitializeHostDeviceProperties();
	this->InitializeDeviceFactory();
}

HostFactory::HostFactory()
	: HostFactory(std::make_unique<DeviceIdRetriever>())
{
}

std::unique_ptr<Host> HostFactory::Create()
{
	// LIGHTBAR = 0xF3
	auto const hostDevices = this->GetHostDevices(m_deviceId);
	auto const devices = this->CreateRequiredDevices(hostDevices);
	return std::make_unique<Host>(m_deviceId, devices);
}

void HostFactory::InitializeHostDeviceProperties()
{
	InitializeSingleZoneKBs();
	InitializeTripleZoneKBs();
	InitializeTripleZoneKBsWithPeripherals();
}

bool HostFactory::InitializeDeviceFactory()
{
	m_deviceId = m_devIdRetriever->GetDeviceID();

	DeviceChannelFactory devChannelFactory{};
	auto pDevChannel = devChannelFactory.Create(this->GetDeviceChannelType(m_deviceId));

	m_devFactory = std::make_unique<DeviceFactory>(std::move(pDevChannel));

	return (m_deviceId && m_devFactory);
}

std::vector<std::shared_ptr<IDevice>> HostFactory::CreateRequiredDevices(DeviceMask deviceTypes)
{
	std::vector<std::shared_ptr<IDevice>> devices{};

	if (!!(deviceTypes & DeviceMask::Keyboard))
	{
		auto const keyboardType = this->GetKeyboardType(m_deviceId);
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

KeyboardType HostFactory::GetKeyboardType(uint32_t deviceId) const
{
	auto const result = m_deviceIdToDevProps.find(deviceId);
	return (result != m_deviceIdToDevProps.cend()) ? result->second.kbType : KeyboardType::NONE;
}

DeviceChannelType HostFactory::GetDeviceChannelType(uint32_t deviceId) const
{
	auto const result = m_deviceIdToDevProps.find(deviceId);
	return (result != m_deviceIdToDevProps.cend()) ? result->second.deviceChannelType : DeviceChannelType::None;
}

DeviceMask HostFactory::GetHostDevices(uint32_t deviceId) const
{
	auto const result = m_deviceIdToDevProps.find(deviceId);
	return (result != m_deviceIdToDevProps.cend()) ? result->second.devices : DeviceMask::Unknown;
}

void HostFactory::InitializeSingleZoneKBs()
{
	std::array<uint32_t, 9> constexpr SINGLE_ZONE_INSYDE_DEVICE_IDS
	{
		DEVICE_ID_NP50RXX, DEVICE_ID_NH70XX, DEVICE_ID_NKNP50XX,
		DEVICE_ID_PC50DXX, DEVICE_ID_A715XX, DEVICE_ID_NP50SXX,
		DEVICE_ID_CV15XX, DEVICE_ID_NP60SXX, DEVICE_ID_V360EXX
		//, DEVICE_ID_NH77XX
	};

	for (auto const currentDeviceId : SINGLE_ZONE_INSYDE_DEVICE_IDS)
	{
		m_deviceIdToDevProps[currentDeviceId].devices = DeviceMask::Keyboard;
		m_deviceIdToDevProps[currentDeviceId].kbType = KeyboardType::SINGLE_ZONE;
		m_deviceIdToDevProps[currentDeviceId].deviceChannelType = DeviceChannelType::Insyde;
	}
}

void HostFactory::InitializeTripleZoneKBs()
{
	m_deviceIdToDevProps[DEVICE_ID_P650RS_G].devices = DeviceMask::Keyboard;
	m_deviceIdToDevProps[DEVICE_ID_P650RS_G].kbType = KeyboardType::TRIPLE_ZONE;
	m_deviceIdToDevProps[DEVICE_ID_P650RS_G].deviceChannelType = DeviceChannelType::Wmi;
}

void HostFactory::InitializeTripleZoneKBsWithPeripherals()
{
	m_deviceIdToDevProps[DEVICE_ID_FAKE].devices = DeviceMask::Keyboard | DeviceMask::Lightbar | DeviceMask::Logo;
	m_deviceIdToDevProps[DEVICE_ID_FAKE].kbType = KeyboardType::TRIPLE_ZONE;
	m_deviceIdToDevProps[DEVICE_ID_FAKE].deviceChannelType = DeviceChannelType::Fake;
}