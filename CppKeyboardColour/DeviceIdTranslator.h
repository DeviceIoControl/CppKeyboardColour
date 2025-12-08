// Created by DeviceIoControl

#pragma once

#include "stdafx.h"
#include "DeviceIds.h"
#include "KeyboardType.h"
#include "IDeviceIdTranslator.h"

struct KB_PROPERTIES
{
	KeyboardType kbType;
	KBCommunicatorType kbCommunicatorType;
};

// NOTE: Add more Device IDs as more keyboards become supported.
class DeviceIdTranslator 
	: public IDeviceIdTranslator
{
public:
	DeviceIdTranslator() 
	{
		m_deviceIdToKBProps[DEVICE_ID_NP50RXX].kbType = KeyboardType::SINGLE_ZONE;
		m_deviceIdToKBProps[DEVICE_ID_NP50RXX].kbCommunicatorType = KBCommunicatorType::Insyde;

		m_deviceIdToKBProps[DEVICE_ID_NH70XX].kbType = KeyboardType::SINGLE_ZONE;
		m_deviceIdToKBProps[DEVICE_ID_NH70XX].kbCommunicatorType = KBCommunicatorType::Insyde;

		m_deviceIdToKBProps[DEVICE_ID_P650RS_G].kbType = KeyboardType::TRIPLE_ZONE;
		m_deviceIdToKBProps[DEVICE_ID_P650RS_G].kbCommunicatorType = KBCommunicatorType::Wmi;

		m_deviceIdToKBProps[DEVICE_ID_FAKE].kbType = KeyboardType::TRIPLE_ZONE;
		m_deviceIdToKBProps[DEVICE_ID_FAKE].kbCommunicatorType = KBCommunicatorType::Fake;
	}

	KeyboardType TranslateToKBType(uint32_t deviceId) const override
	{
		auto const result = m_deviceIdToKBProps.find(deviceId);
		return (result != m_deviceIdToKBProps.cend()) ? result->second.kbType : KeyboardType::NONE;
	}

	KBCommunicatorType DeviceIdToKBCommunicatorType(uint32_t deviceId) const override
	{
		auto const result = m_deviceIdToKBProps.find(deviceId);
		return (result != m_deviceIdToKBProps.cend()) ? result->second.kbCommunicatorType : KBCommunicatorType::None;
	}

	~DeviceIdTranslator() override = default;

private:
	std::map<uint32_t, KB_PROPERTIES> m_deviceIdToKBProps{};
};