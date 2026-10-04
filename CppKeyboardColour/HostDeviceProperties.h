// Created by DeviceIoControl

#pragma once

#include "Devices/DeviceMask.h"
#include "Common/KeyboardType.h"
#include "Channels/DeviceChannelType.h"

struct HOST_DEVICE_PROPS
{
	KeyboardType kbType;
	DeviceMask devices;
	DeviceChannelType deviceChannelType;
	std::wstring modelName;
};
