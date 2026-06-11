#include "stdafx.h"
#include "KeyboardOperationsHandler.h"
#include "ThemeCommandLine.h"
#include "CommandLine.h"
#include "ConsoleUtils.h"

DWORD DoKeyboardOperation(IKeyboard* pKeyboard, const std::vector<std::wstring>& cmdLines)
{
	std::unique_ptr<IAnimation> pAnimation{};
	auto backlight = BacklightType::Invalid;
	auto sysAnimation = SystemAnimation::KB_MODE_CUSTOM;

	switch (ProcessCmdThemeFlags(cmdLines))
	{
	case ThemeFlags::Animation:
		pAnimation = ProcessThemeCommandLine(cmdLines);
		break;

	case ThemeFlags::InBuilt:
		sysAnimation = ProcessSystemAnimationCommandLine(cmdLines);
		break;

	case ThemeFlags::Backlight:
		backlight = ProcessBacklightCommandLine(cmdLines);
		break;

		// The above code logic should ensure that we NEVER reach here.
	default:
		return ERROR_FAIL_FAST_EXCEPTION;
	}

	if (backlight != BacklightType::Invalid)
	{
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

	if (sysAnimation != SystemAnimation::KB_MODE_CUSTOM)
	{
		std::cout << "Playing Inbuilt Keyboard animation...\n";
		pKeyboard->SendCode(xstd::to_underlying(sysAnimation));
		return 0;
	}

	if (pAnimation)
	{
		// "-speed" command-line is only valid with an animation.
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

	std::cout << "Exiting...\n";

	return 1;
}