// Created by DeviceIoControl

#include "stdafx.h"
#include "CommandLine.h"
#include "ThemeCommandLine.h"
#include "SystemAnimationTranslator.h"

ThemeFlags ProcessCmdThemeFlags(const std::vector<std::wstring>& cmdLines)
{
	if (CommandLine::Contains(L"inbuilt", cmdLines))
	{
		return ThemeFlags::InBuilt;
	}

	if (CommandLine::Contains(L"theme", cmdLines))
	{
		return ThemeFlags::Animation;
	}

	if (CommandLine::Contains(L"backlight", cmdLines))
	{
		return ThemeFlags::Backlight;
	}

	return ThemeFlags::FlagInvalid;
}

BacklightType ProcessBacklightCommandLine(const std::vector<std::wstring>& cmdLines)
{
	auto const ourCmds = CommandLine::GetCommandsAfter(L"backlight", cmdLines);

	if (ourCmds.empty()) 
	{
		return BacklightType::Invalid;
	}

	if (CommandLine::Contains(L"on", ourCmds))
	{
		return BacklightType::On;
	}

	if (CommandLine::Contains(L"off", ourCmds))
	{
		return BacklightType::Off;
	}

	std::cout << "Invalid backlight operation name was provided.\n";

	return BacklightType::Invalid;
}

SystemAnimation ProcessSystemAnimationCommandLine(const std::vector<std::wstring>& cmdLines)
{
	SystemAnimationTranslator const sysAnimTranslator{};
	auto const ourCmds = CommandLine::GetCommandsAfter(L"inbuilt", cmdLines);

	if (ourCmds.empty())
	{
		std::cout << "Invalid inbuilt animation command.\n";
		return SystemAnimation::KB_MODE_CUSTOM;
	}

	auto const sysAnimation = sysAnimTranslator.Translate(ourCmds.front());

	if (sysAnimation == SystemAnimation::KB_MODE_CUSTOM)
	{
		std::cout << "Invalid inbuilt animation name was provided.\n";
	}

	return sysAnimation;
}

std::unique_ptr<IAnimation> ProcessThemeCommandLine(const std::vector<std::wstring>& cmdLines)
{
	auto const ourCmds = CommandLine::GetCommandsAfter(L"theme", cmdLines);

	if (ourCmds.empty()) 
	{
		std::cout << "Invalid theme command.\n";
		return nullptr;
	}

	if (CommandLine::Contains(L"breathe", ourCmds))
	{
		return std::make_unique<BreatheAnimation>();
	}
	else if (CommandLine::Contains(L"colourshift", ourCmds))
	{
		return std::make_unique<ColourShiftAnimation>();
	}
	else if (CommandLine::Contains(L"freshbreathe", ourCmds))
	{
		return std::make_unique<FreshBreatheAnimation>();
	}
	else if (CommandLine::Contains(L"colourtransform", ourCmds))
	{
		return std::make_unique<ColourTransformAnimation>();
	}
	else if (CommandLine::Contains(L"blink", ourCmds))
	{
		return std::make_unique<PulsatingBlinkAnimation>();
	}
	else if (CommandLine::Contains(L"heartbeat", ourCmds))
	{
		return std::make_unique<HeartbeatAnimation>();
	}

	std::cout << "Invalid animation name was provided!\n";

	return nullptr;
}