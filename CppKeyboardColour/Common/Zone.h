// Created by DeviceIoControl

#pragma once
#include "stdafx.h"

enum class Zone : uint8_t
{
	LEFT = 0xF0,
	MID = 0xF1,
	RIGHT = 0xF2,
	ALL = 0xFF
};

inline constexpr uint32_t ZoneToArrayIndex(Zone zone)
{
	return xstd::to_underlying(zone) - xstd::to_underlying(Zone::LEFT);
}