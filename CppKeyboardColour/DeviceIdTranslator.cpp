// Created by DeviceIoControl

#include "stdafx.h"
#include "DeviceIdTranslator.h"
#include "DeviceIds.h"

DeviceIdTranslator::DeviceIdTranslator()
{
	this->InitializeSingleZoneKBs();
	this->InitializeTripleZoneKBs();
}

KeyboardType DeviceIdTranslator::TranslateToKBType(uint32_t deviceId) const
{
	auto const result = m_deviceIdToKBProps.find(deviceId);
	return (result != m_deviceIdToKBProps.cend()) ? result->second.kbType : KeyboardType::NONE;
}

KBCommunicatorType DeviceIdTranslator::TranslateToKBCommType(uint32_t deviceId) const
{
	auto const result = m_deviceIdToKBProps.find(deviceId);
	return (result != m_deviceIdToKBProps.cend()) ? result->second.kbCommsType : KBCommunicatorType::None;
}

void DeviceIdTranslator::InitializeSingleZoneKBs()
{
	std::array<uint32_t, 4> constexpr singleZoneDeviceIds
	{
		DEVICE_ID_NP50RXX, DEVICE_ID_NH70XX, DEVICE_ID_NKNP50XX,
		DEVICE_ID_PC50DXX // DEVICE_ID_NH77XX
	};

	for (auto const currentDeviceId : singleZoneDeviceIds)
	{
		m_deviceIdToKBProps[currentDeviceId].kbType = KeyboardType::SINGLE_ZONE;
		m_deviceIdToKBProps[currentDeviceId].kbCommsType = KBCommunicatorType::Insyde;
	}
}

void DeviceIdTranslator::InitializeTripleZoneKBs()
{
	m_deviceIdToKBProps[DEVICE_ID_P650RS_G].kbType = KeyboardType::TRIPLE_ZONE;
	m_deviceIdToKBProps[DEVICE_ID_P650RS_G].kbCommsType = KBCommunicatorType::Wmi;

	m_deviceIdToKBProps[DEVICE_ID_FAKE].kbType = KeyboardType::TRIPLE_ZONE;
	m_deviceIdToKBProps[DEVICE_ID_FAKE].kbCommsType = KBCommunicatorType::Fake;
}