// Created by DeviceIoControl

#include "stdafx.h"
#include "CommandLine.h"
#include "ThemeCommandLine.h"

std::unique_ptr<IAnimation> ProcessThemeCommandLine(const std::vector<std::wstring>& cmdLines)
{
	if (CommandLine::Contains(L"breathe", cmdLines))
	{
		return std::make_unique<BreatheAnimation>();
	}
	else if (CommandLine::Contains(L"colourshift", cmdLines))
	{
		return std::make_unique<ColourShiftAnimation>();
	}
	else if (CommandLine::Contains(L"freshbreathe", cmdLines))
	{
		return std::make_unique<FreshBreatheAnimation>();
	}
	else if (CommandLine::Contains(L"colourtransform", cmdLines))
	{
		return std::make_unique<ColourTransformAnimation>();
	}
	else if (CommandLine::Contains(L"blink", cmdLines))
	{
		return std::make_unique<PulsatingBlinkAnimation>();
	}
	else if (CommandLine::Contains(L"heartbeat", cmdLines))
	{
		return std::make_unique<HeartbeatAnimation>();
	}

	return nullptr;
}