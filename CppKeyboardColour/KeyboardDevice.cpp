// Created by DeviceIoControl

#include "stdafx.h"
#include "KeyboardDevice.h"
#include "DeviceIds.h"

KeyboardDevice::KeyboardDevice(bool fakeDevice /*= false*/)
	: m_useFakeDeviceId(fakeDevice),
	m_pDevIdRetriever(std::make_unique<DeviceIdRetriever>())
{
	this->InitializeSingleZoneKBs();
	this->InitializeTripleZoneKBs();
}

uint32_t KeyboardDevice::GetDeviceId() const 
{
	if (m_pDevIdRetriever && !m_useFakeDeviceId)
	{
		// We could cache this value, but this should only be called once anyways.
		return m_pDevIdRetriever->GetDeviceID();
	}

	return m_useFakeDeviceId ? DEVICE_ID_FAKE : 0xFFFFFFFF;
}

KeyboardType KeyboardDevice::GetKeyboardType() const
{
	auto const result = m_deviceIdToKBProps.find(this->GetDeviceId());
	return (result != m_deviceIdToKBProps.cend()) ? result->second.kbType : KeyboardType::NONE;
}

KBCommunicatorType KeyboardDevice::GetKBCommunicatorType() const 
{
	auto const result = m_deviceIdToKBProps.find(this->GetDeviceId());
	return (result != m_deviceIdToKBProps.cend()) ? result->second.kbCommsType : KBCommunicatorType::None;
}

void KeyboardDevice::InitializeSingleZoneKBs()
{
	std::array<uint32_t, 9> constexpr SINGLE_ZONE_DEVICE_IDS
	{
		DEVICE_ID_NP50RXX, DEVICE_ID_NH70XX, DEVICE_ID_NKNP50XX,
		DEVICE_ID_PC50DXX, DEVICE_ID_A715XX, DEVICE_ID_NP50SXX,
		DEVICE_ID_CV15XX, DEVICE_ID_NP60SXX, DEVICE_ID_V360ENXX
		//, DEVICE_ID_NH77XX
	};

	for (auto const currentDeviceId : SINGLE_ZONE_DEVICE_IDS)
	{
		m_deviceIdToKBProps[currentDeviceId].kbType = KeyboardType::SINGLE_ZONE;
		m_deviceIdToKBProps[currentDeviceId].kbCommsType = KBCommunicatorType::Insyde;
	}
}

void KeyboardDevice::InitializeTripleZoneKBs()
{
	m_deviceIdToKBProps[DEVICE_ID_P650RS_G].kbType = KeyboardType::TRIPLE_ZONE;
	m_deviceIdToKBProps[DEVICE_ID_P650RS_G].kbCommsType = KBCommunicatorType::Wmi;

	m_deviceIdToKBProps[DEVICE_ID_FAKE].kbType = KeyboardType::TRIPLE_ZONE;
	m_deviceIdToKBProps[DEVICE_ID_FAKE].kbCommsType = KBCommunicatorType::Fake;
}
