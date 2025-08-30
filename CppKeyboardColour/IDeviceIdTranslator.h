#pragma once

#include "stdafx.h"
#include "KeyboardType.h"

class IDeviceIdTranslator 
{
public:
	virtual ~IDeviceIdTranslator() = default;

	virtual KeyboardType TranslateToKBType(uint32_t deviceId) const = 0;
	virtual KBCommunicatorType DeviceIdToKBCommunicatorType(uint32_t deviceId) const = 0;
};