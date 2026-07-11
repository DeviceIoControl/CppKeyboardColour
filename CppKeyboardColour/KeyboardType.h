// Created by DeviceIoControl

#pragma once

#include "stdafx.h"

enum class KeyboardType : uint16_t
{
	NONE,
	TRIPLE_ZONE,
	SINGLE_ZONE,
	TRIPLE_ZONE_LIGHTBAR,
};

enum class KBCommunicatorType : uint16_t
{
	None,
	Fake = 1,
	Wmi = 2,
	Insyde = 3
};