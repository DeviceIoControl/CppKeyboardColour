// Created by DeviceIoControl

#pragma once

enum class DeviceMask : uint16_t
{
	Unknown = 0,
	Keyboard = 1,
	Lightbar = 2,
	Logo = 4,
};