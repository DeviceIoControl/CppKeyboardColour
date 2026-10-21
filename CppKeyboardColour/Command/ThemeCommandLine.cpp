// Created by DeviceIoControl

#include "stdafx.h"

#include "CommandLine.h"
#include "ThemeCommandLine.h"
#include "../ColourFactory.h"
#include "../Console/Logger.h"
#include "../Animations/AnimationFactory.h"
#include "../Animations/SystemAnimationTranslator.h"

BacklightType ProcessBacklightCommandLine(const std::vector<std::wstring>& cmdLines)
{
	const auto ourCmds = CommandLine::GetCommandsAfter(L"backlight", cmdLines);

	if (ourCmds.empty())
	{
		KB_ERROR(L"Invalid backlight operation command.");
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

	KB_ERROR(L"Invalid backlight operation was provided.");

	return BacklightType::Invalid;
}

SystemAnimation ProcessSystemAnimationCommandLine(const std::vector<std::wstring>& cmdLines)
{
	SystemAnimationTranslator const sysAnimTranslator{};
	const auto ourCmds = CommandLine::GetCommandsAfter(L"inbuilt", cmdLines);

	if (ourCmds.empty())
	{
		KB_ERROR(L"Invalid inbuilt animation command.");
		return SystemAnimation::KB_MODE_CUSTOM;
	}

	const auto sysAnimation = sysAnimTranslator.Translate(ourCmds.front());

	if (sysAnimation == SystemAnimation::KB_MODE_CUSTOM)
	{
		KB_ERROR(L"Invalid inbuilt animation name was provided.");
	}

	return sysAnimation;
}

std::unique_ptr<IAnimation> ProcessThemeCommandLine(const std::vector<std::wstring>& cmdLines)
{
	const auto ourCmds = CommandLine::GetCommandsAfter(L"theme", cmdLines);

	if (ourCmds.empty())
	{
		KB_ERROR(L"Invalid theme command.");
		return nullptr;
	}

	AnimationFactory const factory{};

	if (auto pAnimation = factory.Create(ourCmds[0])) 
	{
		return pAnimation;
	}

	KB_ERROR(L"Invalid animation name was provided!");

	return nullptr;
}

std::optional<Colour> ProcessColourCommandLine(const std::vector<std::wstring>& cmdLines)
{
	if (const auto afterCmdLine = CommandLine::GetCommandsAfter(L"colour", cmdLines); !afterCmdLine.empty())
	{
		if (const auto parsedColour = xstd::stoi(afterCmdLine[0], 16))
		{
			ColourFactory factory{};
			return factory.Create(parsedColour.value());
		}
	}

	return std::nullopt;
}

std::optional<Colours> ProcessColoursCommandLine(const std::vector<std::wstring>& cmdLines)
{
	if (const auto afterCmdLine = CommandLine::GetCommandsAfter(L"colours", cmdLines); !afterCmdLine.empty())
	{
		if (afterCmdLine.size() < 3)
		{
			return std::nullopt;
		}

		const auto leftZoneColour = xstd::stoi(afterCmdLine[0], 16);
		const auto midZoneColour = xstd::stoi(afterCmdLine[1], 16);
		const auto rightZoneColour = xstd::stoi(afterCmdLine[2], 16);

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

std::optional<Colour> ProcessLightbarCommandLine(const std::vector<std::wstring>& cmdLines) 
{
	if (const auto afterCmdLine = CommandLine::GetCommandsAfter(L"lightbar", cmdLines); !afterCmdLine.empty())
	{
		if (const auto parsedColour = xstd::stoi(afterCmdLine[0], 16))
		{
			ColourFactory factory{};
			return factory.Create(parsedColour.value());
		}
	}

	return std::nullopt;
}

float ProcessSpeedCommandLine(const std::vector<std::wstring>& cmdLines)
{
	if (const auto afterCmdLine = CommandLine::GetCommandsAfter(L"--speed", cmdLines); !afterCmdLine.empty())
	{
		if (const auto val = xstd::stoi(afterCmdLine[0]))
		{
			return val.value() / 100.0f;
		}

		KB_WARN(L"Failed to parse speed input! Fallback to default speed.");
	}

	return 1.0f; // default speed
}

CmdOperation ProcessCmdOperation(const std::vector<std::wstring>& cmdLines)
{
	if (CommandLine::Contains(L"inbuilt", cmdLines))
	{
		return CmdOperation::InBuilt;
	}

	if (CommandLine::Contains(L"theme", cmdLines))
	{
		return CmdOperation::Animation;
	}

	if (CommandLine::Contains(L"backlight", cmdLines))
	{
		return CmdOperation::Backlight;
	}

	if (CommandLine::Contains(L"colour", cmdLines))
	{
		return CmdOperation::UserColour;
	}

	if (CommandLine::Contains(L"colours", cmdLines))
	{
		return CmdOperation::UserColour3;
	}

	if (CommandLine::Contains(L"lightbar", cmdLines))
	{
		return CmdOperation::Lightbar;
	}

	return CmdOperation::FlagInvalid;
}