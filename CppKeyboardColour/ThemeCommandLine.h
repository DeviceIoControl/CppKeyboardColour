// Created by DeviceIoControl

#pragma once
#include "IAnimation.h"
#include "SystemAnimation.h"

enum class ThemeFlags
{
	FlagInvalid,
	Animation,
	InBuilt,
	Backlight,
	UserColour,
	UserColour3
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
std::optional<Colour> ProcessColourCommandLine(const std::vector<std::wstring>& cmdLines);
std::optional<Colours> ProcessColoursCommandLine(const std::vector<std::wstring>& cmdLines);
float ProcessSpeedCommandLine(const std::vector<std::wstring>& cmdLines);
