// Created by DeviceIoControl

#include "stdafx.h"
#include "CommandLine.h"
#include "HostFactory.h"
#include "SingleInstanceEvent.h"
#include "CommandOperationsHandler.h"
#include "ConsoleUtils.h"

#pragma warning(disable: 4995)

static void DisplayHostInformation(const IHost* pHost)
{
	std::cout << "Host Devices: " << pHost->GetDevices() << "\n";
	
	if (!!(pHost->GetDevices() & DeviceMask::Keyboard))
	{
		std::cout << "Keyboard Type: " << pHost->GetKeyboardType() << "\n";
	}

	std::wcout << L"Model Name: " << pHost->GetModelName() << L"\n\n";
}

int wmain(int argc, const wchar_t* argv[])
{
	SetConsoleTitleA(PROGRAM_BOOTSTRAP_STRING);
	std::cout << PROGRAM_BOOTSTRAP_STRING << "\n\n";

	if (!IsSingleInstance())
	{
		std::cout << "You can only have 1 instance of this program running. Please close any other instances.\n";
		WaitForEnterIfNeeded();
		return ERROR_ALREADY_EXISTS;
	}

	const auto cmdLines = CommandLine::GetCommandLines(argc, argv);
	const auto enableDeviceMonitorMode = CommandLine::Contains(L"--dmm", cmdLines);

	HostFactory hostFactory(USE_DEBUGGABLE_HOST, enableDeviceMonitorMode);
	auto pHost = hostFactory.Create();

	if (!pHost)
	{
		std::cout << "This system is not supported.\n\nPlease request for support using the following URL: https://github.com/DeviceIoControl/CppKeyboardColour/issues/new.\n";
		WaitForEnterIfNeeded();
		return ERROR_NOT_SUPPORTED;
	}

	DisplayHostInformation(pHost.get());

	if (enableDeviceMonitorMode)
	{
		std::cout << "WARNING: Device monitor mode enabled! (Performance may be affected)\n\n";
	}

	if (!CommandLine::ExclusiveContains({ L"theme", L"inbuilt", L"backlight", L"colour", L"colours", L"lightbar" }, cmdLines))
	{
		std::cout << "Invalid command line. Command is: CLEVO_KeyboardColour.exe theme/inbuilt/backlight/lightbar/colour(s) [<themeName>/<hexColour>] [--once] [--speed] <speed> [--dmm]\n";
		WaitForEnterIfNeeded();
		return ERROR_INVALID_PARAMETER;
	}

	return DoCommandOperation(std::move(pHost), cmdLines);
}
