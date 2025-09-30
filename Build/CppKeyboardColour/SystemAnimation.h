// Created by DeviceIoControl

#pragma once

#include "stdafx.h"

// In-built keyboard animations.
enum class SystemAnimation : uint32_t
{
	KB_MODE_OFF = 0xFFFFFFFE,
	KB_MODE_STANDARD = 0xEFFFFFFF,
	KB_MODE_WAVE = 0xB0000000, // Works but has side-effects.
	KB_MODE_CYCLE = 0x33010000,
	KB_MODE_DANCE = 0x80000000,
	KB_MODE_FLASH = 0xA0000000, // Works but has side-effects.
	KB_MODE_TEMPO = 0x90000000, // Works but has side-effects.
	KB_MODE_CUSTOM = 0x00000000,
	KB_MODE_BREATHE = 0x1002A000, // Works but has side-effects.
	KB_MODE_RANDOM_COLOUR = 0x70000000  // Works but has side-effects.
};