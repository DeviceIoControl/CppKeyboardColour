// Created by DeviceIoControl

#pragma once

struct HOST_DEVICE_PROPS
{
	KeyboardType kbType;
	DeviceMask devices;
	DeviceChannelType deviceChannelType;
	std::wstring modelName;
};
