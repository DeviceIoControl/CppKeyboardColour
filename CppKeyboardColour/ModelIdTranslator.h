// Created by DeviceIoControl

#pragma once
#include "KeyboardType.h"
#include "DeviceChannelType.h"
#include "DeviceMask.h"

struct HOST_DEVICE_PROPS
{
	KeyboardType kbType;
	DeviceMask devices;
	DeviceChannelType deviceChannelType;
};

class ModelIdTranslator 
{
public:
	ModelIdTranslator();
	~ModelIdTranslator() = default;

	KeyboardType GetKeyboardType(uint32_t modelId) const;
	DeviceChannelType GetDeviceChannelType(uint32_t modelId) const;
	DeviceMask GetHostDevices(uint32_t modelId) const;

private:
	std::map<uint32_t, HOST_DEVICE_PROPS> m_modelIdToDevProps{};

	void InitializeSingleZoneKBs();
	void InitializeTripleZoneKBs();
	void InitializeTripleZoneKBsWithPeripherals();
};