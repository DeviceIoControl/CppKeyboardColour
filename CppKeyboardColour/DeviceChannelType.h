// Created by DeviceIoControl

#pragma once

enum class DeviceChannelType : uint16_t
{
	None,
	Debug = 1,
	Wmi = 2,
	Insyde = 3
};
