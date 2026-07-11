// Created by DeviceIoControl

#pragma once

#include "stdafx.h"
#include "KeyboardType.h"

class IKeyboardDevice
{
public:
	virtual ~IKeyboardDevice() = default;

	virtual uint32_t GetDeviceId() const = 0;
	virtual KeyboardType GetKeyboardType() const = 0;
	virtual KBCommunicatorType GetKBCommunicatorType() const = 0;
};