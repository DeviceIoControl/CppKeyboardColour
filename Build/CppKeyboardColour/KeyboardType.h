// Created by DeviceIoControl

#pragma once

#include "stdafx.h"

enum class KeyboardType : uint16_t
{
	NONE,
	TRIPLE_ZONE,
	SINGLE_ZONE,
	PER_KEY,
};

enum class KBCommunicatorType : uint16_t
{
	None,
	Fake = 1,
	Wmi = 2,
	Insyde = 3
};