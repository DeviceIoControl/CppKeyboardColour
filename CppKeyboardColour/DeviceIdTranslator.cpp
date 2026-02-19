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
	m_deviceIdToKBProps[DEVICE_ID_NP50RXX].kbType = KeyboardType::SINGLE_ZONE;
	m_deviceIdToKBProps[DEVICE_ID_NP50RXX].kbCommsType = KBCommunicatorType::Insyde;

	m_deviceIdToKBProps[DEVICE_ID_NH70XX].kbType = KeyboardType::SINGLE_ZONE;
	m_deviceIdToKBProps[DEVICE_ID_NH70XX].kbCommsType = KBCommunicatorType::Insyde;

	m_deviceIdToKBProps[DEVICE_ID_NKNP50XX].kbType = KeyboardType::SINGLE_ZONE;
	m_deviceIdToKBProps[DEVICE_ID_NKNP50XX].kbCommsType = KBCommunicatorType::Insyde;

	// m_deviceIdToKBProps[DEVICE_ID_NH77XX].kbType = KeyboardType::SINGLE_ZONE;
	// m_deviceIdToKBProps[DEVICE_ID_NH77XX].kbCommsType = KBCommunicatorType::Insyde;
}

void DeviceIdTranslator::InitializeTripleZoneKBs()
{
	m_deviceIdToKBProps[DEVICE_ID_P650RS_G].kbType = KeyboardType::TRIPLE_ZONE;
	m_deviceIdToKBProps[DEVICE_ID_P650RS_G].kbCommsType = KBCommunicatorType::Wmi;

	m_deviceIdToKBProps[DEVICE_ID_FAKE].kbType = KeyboardType::TRIPLE_ZONE;
	m_deviceIdToKBProps[DEVICE_ID_FAKE].kbCommsType = KBCommunicatorType::Fake;
}