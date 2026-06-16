// Created by DeviceIoControl

#include "stdafx.h"
#include "KeyboardOperationsHandler.h"
#include "ThemeCommandLine.h"
#include "CommandLine.h"
#include "ConsoleUtils.h"

static DWORD DoKeyboardBacklightOperation(IKeyboard* pKeyboard, BacklightType backlight)
{
	if (backlight == BacklightType::Invalid)
	{
		return ERROR_INVALID_PARAMETER;
	}

	switch (backlight)
	{
	case BacklightType::On:
		std::cout << "Turning keyboard lights on.\n";
		pKeyboard->SetBacklightOn();
		break;

	case BacklightType::Off:
		std::cout << "Turning keyboard lights off.\n";
		pKeyboard->SetBacklightOff();
		break;
	}

	return 0;
}

static DWORD DoKeyboardThemeOperation(IKeyboard* pKeyboard, std::unique_ptr<IAnimation> pAnimation, const std::vector<std::wstring>& cmdLines)
{
	if (!pAnimation)
	{
		return ERROR_INVALID_PARAMETER;
	}

	// "--speed" command-line is only valid with an animation.
	auto const speedFactor = ProcessSpeedCommandLine(cmdLines);

	if (!pKeyboard->SetSpeedFactor(speedFactor))
	{
		std::cout << "Speed value out of range (1-250). Animation will not play.\n";
		WaitForEnterIfNeeded();
		return ERROR_INVALID_PARAMETER;
	}

	if (speedFactor != 1.0f)
	{
		std::cout << "Custom speed: " << (100 * speedFactor) << "%\n";
	}

	auto const bShouldLoop = !CommandLine::Contains(L"--once", cmdLines);
	pKeyboard->PlayAnimation(*pAnimation, bShouldLoop);
	return 0;
}

static DWORD DoKeyboardSystemAnimationOperation(IKeyboard* pKeyboard, SystemAnimation sysAnimation)
{
	if (sysAnimation == SystemAnimation::KB_MODE_CUSTOM)
	{
		return ERROR_INVALID_PARAMETER;
	}

	std::cout << "Playing Inbuilt Keyboard animation...\n";
	pKeyboard->SendCode(xstd::to_underlying(sysAnimation));

	return 0;
}

static DWORD DoKeyboardUserColourOperation(IKeyboard* pKeyboard, std::optional<Colour> colour)
{
	if (!colour.has_value())
	{
		return ERROR_INVALID_PARAMETER;
	}

	std::cout << "Setting user provided colour...\n";

	pKeyboard->SetColour(
		colour->at(INDEX_COLOUR_RED),
		colour->at(INDEX_COLOUR_GREEN),
		colour->at(INDEX_COLOUR_BLUE),
		Zone::ALL
	);

	return 0;
}

static DWORD DoKeyboardUserColour3Operation(IKeyboard* pKeyboard, std::optional<Colours> colours)
{
	// Somewhat unsafe, but pKeyboard should be valid before we get here.

	if (pKeyboard->GetKBType() != KeyboardType::TRIPLE_ZONE)
	{
		std::cout << "This operation is not supported on this keyboard type.\n";
		WaitForEnterIfNeeded();
		return 0;
	}

	if (!colours.has_value() || colours->size() != 3)
	{
		std::cout << "Invalid argument: Must be 3 hexadecimal colours specified.\n";
		WaitForEnterIfNeeded();
		return ERROR_INVALID_PARAMETER;
	}

	std::cout << "Setting user provided zone colours...\n";

	for (size_t i = 0; i < colours->size(); ++i)
	{
		auto const& colour = colours->at(i);
		
		pKeyboard->SetColour(
			colour[INDEX_COLOUR_RED],
			colour[INDEX_COLOUR_GREEN],
			colour[INDEX_COLOUR_BLUE],
			static_cast<Zone>(i)
		);
	}

	return 0;
}

DWORD DoKeyboardOperation(IKeyboard* pKeyboard, const std::vector<std::wstring>& cmdLines)
{
	// pKeyboard will always be valid before reaching here, so no need to check the pointer again.

	std::optional<Colour> userColour{};
	std::optional<Colours> userColours{};
	std::unique_ptr<IAnimation> pAnimation{};
	auto backlight = BacklightType::Invalid;
	auto sysAnimation = SystemAnimation::KB_MODE_CUSTOM;

	switch (ProcessCmdThemeFlags(cmdLines))
	{
	case ThemeFlags::Animation:
		pAnimation = ProcessThemeCommandLine(cmdLines);
		return DoKeyboardThemeOperation(pKeyboard, std::move(pAnimation), cmdLines);

	case ThemeFlags::InBuilt:
		sysAnimation = ProcessSystemAnimationCommandLine(cmdLines);
		return DoKeyboardSystemAnimationOperation(pKeyboard, sysAnimation);

	case ThemeFlags::Backlight:
		backlight = ProcessBacklightCommandLine(cmdLines);
		return DoKeyboardBacklightOperation(pKeyboard, backlight);

	case ThemeFlags::UserColour:
		userColour = ProcessColourCommandLine(cmdLines);
		return DoKeyboardUserColourOperation(pKeyboard, userColour);

	case ThemeFlags::UserColour3:
		userColours = ProcessColoursCommandLine(cmdLines);
		return DoKeyboardUserColour3Operation(pKeyboard, userColours);

		// The above code logic should ensure that we NEVER reach here.
	default:
		return ERROR_FAIL_FAST_EXCEPTION;
	}

	std::cout << "Exiting...\n";

	return 1;
}