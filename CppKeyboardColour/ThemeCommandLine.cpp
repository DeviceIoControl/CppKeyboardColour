// Created by DeviceIoControl

#include "stdafx.h"
#include "ThemeCommandLine.h"

#include "CommandLine.h"
#include "ColourFactory.h"
#include "AnimationFactory.h"
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

	if (CommandLine::Contains(L"colour", cmdLines))
	{
		return ThemeFlags::UserColour;
	}

	if (CommandLine::Contains(L"colours", cmdLines))
	{
		return ThemeFlags::UserColour3;
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

	AnimationFactory const factory{};

	if (auto pAnimation = factory.Create(ourCmds[0])) 
	{
		return pAnimation;
	}

	std::cout << "Invalid animation name was provided!\n";

	return nullptr;
}

std::optional<Colour> ProcessColourCommandLine(const std::vector<std::wstring>& cmdLines)
{
	if (auto const afterCmdLine = CommandLine::GetCommandsAfter(L"colour", cmdLines); !afterCmdLine.empty())
	{
		if (auto const parsedColour = xstd::stoi(afterCmdLine[0], 16))
		{
			ColourFactory factory{};
			return factory.Create(parsedColour.value());
		}
	}

	return std::nullopt;
}

std::optional<Colours> ProcessColoursCommandLine(const std::vector<std::wstring>& cmdLines)
{
	if (auto const afterCmdLine = CommandLine::GetCommandsAfter(L"colours", cmdLines); !afterCmdLine.empty())
	{
		auto const leftZoneColour = xstd::stoi(afterCmdLine[0], 16);
		auto const midZoneColour = xstd::stoi(afterCmdLine[1], 16);
		auto const rightZoneColour = xstd::stoi(afterCmdLine[2], 16);

		if (!leftZoneColour.has_value() || !midZoneColour.has_value() || !rightZoneColour.has_value())
		{
			return std::nullopt;
		}

		ColourFactory factory{};

		return Colours {
			factory.Create(leftZoneColour.value()),
			factory.Create(midZoneColour.value()),
			factory.Create(rightZoneColour.value())
		};
	}

	return std::nullopt;
}

float ProcessSpeedCommandLine(const std::vector<std::wstring>& cmdLines)
{
	if (auto const afterCmdLine = CommandLine::GetCommandsAfter(L"--speed", cmdLines); !afterCmdLine.empty())
	{
		return xstd::stoi(afterCmdLine[0]).value_or(1.0f) / 100.0f;
	}

	return 1.0f; // default speed
}