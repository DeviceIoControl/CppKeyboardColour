// Created by DeviceIoControl

#pragma once

#include "KeyboardType.h"
#include "IDeviceIdTranslator.h"

struct KB_PROPERTIES
{
	KeyboardType kbType;
	KBCommunicatorType kbCommsType;
};

// NOTE: Add more Device IDs as more keyboards become supported.
class DeviceIdTranslator
	: public IDeviceIdTranslator
{
public:
	DeviceIdTranslator();

	KeyboardType TranslateToKBType(uint32_t deviceId) const override;

	KBCommunicatorType TranslateToKBCommType(uint32_t deviceId) const override;

	~DeviceIdTranslator() override = default;

private:
	std::map<uint32_t, KB_PROPERTIES> m_deviceIdToKBProps{};

	void InitializeSingleZoneKBs();
	void InitializeTripleZoneKBs();
};