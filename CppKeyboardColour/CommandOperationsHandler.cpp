// Created by DeviceIoControl

#include "stdafx.h"
#include "CommandOperationsHandler.h"
#include "ThemeCommandLine.h"
#include "CommandLine.h"
#include "ConsoleUtils.h"
#include "Animator.h"
#include "DeviceMask.h"

static DWORD DoBacklightOperation(std::unique_ptr<IHost> pHost, BacklightType backlight)
{
	if (backlight == BacklightType::Invalid)
	{
		return ERROR_INVALID_PARAMETER;
	}

	switch (backlight)
	{
	case BacklightType::On:
		std::cout << "Turning backlights on.\n";
		pHost->SetBacklightOn(DeviceMask::Keyboard | DeviceMask::Lightbar | DeviceMask::Logo);
		break;

	case BacklightType::Off:
		std::cout << "Turning backlights off.\n";
		pHost->SetBacklightOff(DeviceMask::Keyboard | DeviceMask::Lightbar | DeviceMask::Logo);
		break;
	}

	return 0;
}

static DWORD DoThemeOperation(std::unique_ptr<IHost> pHost, std::unique_ptr<IAnimation> pAnimation, const std::vector<std::wstring>& cmdLines)
{
	if (!pAnimation)
	{
		return ERROR_INVALID_PARAMETER;
	}

	Animator animator{ std::move(pHost) };

	// "--speed" command-line is only valid with an animation.
	auto const speedFactor = ProcessSpeedCommandLine(cmdLines);

	if (!animator.SetSpeedFactor(speedFactor))
	{
		std::cout << "Speed value out of range (1-250). Animation will not be played.\n";
		WaitForEnterIfNeeded();
		return ERROR_INVALID_PARAMETER;
	}

	if (speedFactor != 1.0f)
	{
		std::cout << "Custom speed: " << (100 * speedFactor) << "%\n";
	}

	auto const bShouldLoop = !CommandLine::Contains(L"--once", cmdLines);
	animator.Play(pAnimation.get(), bShouldLoop);

	return 0;
}

static DWORD DoSystemAnimationOperation(std::unique_ptr<IHost> pHost, SystemAnimation sysAnimation)
{
	if (sysAnimation == SystemAnimation::KB_MODE_CUSTOM)
	{
		return ERROR_INVALID_PARAMETER;
	}

	std::cout << "Playing Inbuilt Keyboard animation...\n";
	pHost->SendDeviceCode(DeviceMask::Keyboard, xstd::to_underlying(sysAnimation));

	return 0;
}

static DWORD DoUserColourOperation(std::unique_ptr<IHost> pHost, std::optional<Colour> colour)
{
	if (!colour.has_value())
	{
		return ERROR_INVALID_PARAMETER;
	}

	std::cout << "Setting user provided colour...\n";
	pHost->SetColour(DeviceMask::Keyboard,Zone::ALL, colour.value());

	return 0;
}

static DWORD DoUserColour3Operation(std::unique_ptr<IHost> pHost, const std::optional<Colours>& colours)
{
	// Somewhat unsafe, but pHost should always be valid before we get here.

	if (pHost->GetKeyboardType() != KeyboardType::TRIPLE_ZONE)
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
		pHost->SetColour(DeviceMask::Keyboard, static_cast<Zone>(i), colour);
	}

	return 0;
}

DWORD DoCommandOperation(std::unique_ptr<IHost> pHost, const std::vector<std::wstring>& cmdLines)
{
	// pHost will always be valid before reaching here, so no need to check the pointer again.
	
	switch (ProcessCmdOperation(cmdLines))
	{
	case CmdOperation::Animation:
	{
		auto pAnimation = ProcessThemeCommandLine(cmdLines);
		return DoThemeOperation(std::move(pHost), std::move(pAnimation), cmdLines);
	}

	case CmdOperation::InBuilt:
	{
		auto const sysAnimation = ProcessSystemAnimationCommandLine(cmdLines);
		return DoSystemAnimationOperation(std::move(pHost), sysAnimation);
	}

	case CmdOperation::Backlight:
	{
		auto const backlight = ProcessBacklightCommandLine(cmdLines);
		return DoBacklightOperation(std::move(pHost), backlight);
	}

	case CmdOperation::UserColour:
	{
		auto const userColour = ProcessColourCommandLine(cmdLines);
		return DoUserColourOperation(std::move(pHost), userColour);
	}

	case CmdOperation::UserColour3:
	{
		auto const userColours = ProcessColoursCommandLine(cmdLines);
		return DoUserColour3Operation(std::move(pHost), userColours);
	}

	// The above code logic should ensure that we NEVER reach here.
	default:
		return ERROR_FAIL_FAST_EXCEPTION;
	}

	std::cout << "Exiting...\n";

	return 1;
}