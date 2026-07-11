// Created by DeviceIoControl

#pragma once

#include "KeyboardType.h"
#include "IKeyboardDevice.h"
#include "DeviceIdRetriever.h"

struct KB_PROPERTIES
{
	KeyboardType kbType;
	KBCommunicatorType kbCommsType;
};

class KeyboardDevice
	: public IKeyboardDevice
{
public:
	KeyboardDevice(bool fakeDevice = false);
	~KeyboardDevice() = default;

	uint32_t GetDeviceId() const override;
	KeyboardType GetKeyboardType() const override;
	KBCommunicatorType GetKBCommunicatorType() const override;

private:
	std::unique_ptr<DeviceIdRetriever> m_pDevIdRetriever{};
	std::map<uint32_t, KB_PROPERTIES> m_deviceIdToKBProps{};

	void InitializeSingleZoneKBs();
	void InitializeTripleZoneKBs();
};
