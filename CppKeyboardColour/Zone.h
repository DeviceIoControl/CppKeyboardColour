// Created by DeviceIoControl

#pragma once

#include "stdafx.h"

enum class Zone : uint8_t
{
	LEFT = 0xF0,
	MID = 0xF1,
	RIGHT = 0xF2,
	LIGHTBAR = 0xF3,
	ALL = 0xFF
};