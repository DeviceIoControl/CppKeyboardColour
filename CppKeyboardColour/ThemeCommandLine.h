// Created by DeviceIoControl

#pragma once
#include "Animations.h"
#include "SystemAnimation.h"

enum class ThemeFlags
{
	FlagInvalid,
	Animation,
	InBuilt,
	Backlight
};

enum class BacklightType
{
	Off,
	On,
	Invalid
};

ThemeFlags ProcessCmdThemeFlags(const std::vector<std::wstring>& cmdLines);
BacklightType ProcessBacklightCommandLine(const std::vector<std::wstring>& cmdLines);
SystemAnimation ProcessSystemAnimationCommandLine(const std::vector<std::wstring>& cmdLines);
std::unique_ptr<IAnimation> ProcessThemeCommandLine(const std::vector<std::wstring>& cmdLines);