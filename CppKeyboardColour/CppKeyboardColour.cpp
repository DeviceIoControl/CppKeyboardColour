// Created by DeviceIoControl

#include "stdafx.h"
#include "HostFactory.h"
#include "Console/Logger.h"
#include "Command/CommandLine.h"
#include "Console/ConsoleUtils.h"
#include "Utils/SingleInstanceEvent.h"
#include "Command/CommandOperationsHandler.h"

#pragma warning(disable: 4995)

static void DisplayHostInformation(const IHost* pHost)
{
	KB_INFO("Host Devices: %S", xstd::to_wstring(pHost->GetDevices()).c_str());

	if (!!(pHost->GetDevices() & DeviceMask::Keyboard))
	{
		KB_INFO("Keyboard Type: %S", xstd::to_wstring(pHost->GetKeyboardType()).c_str());
	}

	KB_INFO("Keyboard Type: %S", pHost->GetModelName().c_str());
}

static bool ShouldEnableDMM(const std::vector<std::wstring>& cmdLines)
{
#ifdef TEST_BUILD
	return true;
#else
	return CommandLine::Contains(L"--dmm", cmdLines);
#endif
}

int wmain(int argc, const wchar_t* argv[])
{
	AppConsole().SetTitle(PROGRAM_BOOTSTRAP_STRING);
	std::printf("%S\n\n", PROGRAM_BOOTSTRAP_STRING);

	if (!IsSingleInstance())
	{
		KB_SET_FATAL_ERROR(ERROR_ALREADY_EXISTS);
		KB_FATAL("You can only have 1 instance of this program running. Please close any other instances.");
	}
	
	const auto cmdLines = CommandLine::GetCommandLines(argc, argv);
	const auto enableDeviceMonitorMode = ShouldEnableDMM(cmdLines);
	const auto enableHiddenMode = CommandLine::Contains(L"--hide", cmdLines);

	HostFactory hostFactory(USE_DEBUGGABLE_HOST, enableDeviceMonitorMode);
	auto pHost = hostFactory.Create();

	if (!pHost)
	{
		KB_SET_FATAL_ERROR(ERROR_NOT_SUPPORTED);
		KB_FATAL("This system is not supported.\nPlease request for support using the following URL: https://github.com/DeviceIoControl/CppKeyboardColour/issues/new/choose.");
	}

	DisplayHostInformation(pHost.get());

	if (enableDeviceMonitorMode)
	{
		KB_WARN("Device monitor mode enabled! (Performance may be affected)");

		if (enableHiddenMode)
		{
			KB_WARN("Cannot enable hidden mode with Device monitor mode enabled.");
		}
	}

	if (!CommandLine::ExclusiveContains({ L"theme", L"inbuilt", L"backlight", L"colour", L"colours", L"lightbar" }, cmdLines))
	{
		KB_SET_FATAL_ERROR(ERROR_INVALID_PARAMETER);
		KB_FATAL("Invalid command line. Command is: CLEVO_KeyboardColour.exe theme/inbuilt/backlight/lightbar/colour(s) [<themeName>/<hexColour>] [--once] [--speed] <speed> [--dmm] [--hide]");
	}

	EnterHiddenMode(!enableDeviceMonitorMode && enableHiddenMode);

	return DoCommandOperation(std::move(pHost), cmdLines);
}
