// Created by DeviceIoControl

#include "stdafx.h"
#include "HostFactory.h"
#include "Console/Logger.h"
#include "Command/CommandLine.h"
#include "Console/ConsoleUtils.h"
#include "Utils/SingleInstanceEvent.h"
#include "Command/CommandOperationsHandler.h"

#pragma warning(disable: 4995)

namespace
{
	void DisplayHostInformation(const IHost* pHost)
	{
		assert(pHost != nullptr, L"pHost was a nullptr");

		KB_INFO(L"Host Devices: %s", xstd::to_wstring(pHost->GetDevices()).c_str());

		if (!!(pHost->GetDevices() & DeviceMask::Keyboard))
		{
			KB_INFO(L"Keyboard Type: %s", xstd::to_wstring(pHost->GetKeyboardType()).c_str());
		}

		KB_INFO(L"Model Name: %s", pHost->GetModelName().c_str());
	}

	bool ShouldEnableDMM(const std::vector<std::wstring>& cmdLines)
	{
	#ifdef TEST_BUILD
		return true;
	#else
		return CommandLine::Contains(L"--dmm", cmdLines);
	#endif
	}

	std::unique_ptr<ModelIdentifier> CreateModelIdentifier(bool useLegacyModelRetriever, bool useDebugModel)
	{
		return std::make_unique<ModelIdentifier>(useLegacyModelRetriever, useDebugModel);
	}

} // namespace

int wmain(int argc, const wchar_t* argv[])
{
	KB_CONSOLE_TITLE(PROGRAM_BOOTSTRAP_STRING);
	
	if (!IsSingleInstance())
	{
		KB_SET_FATAL_ERROR(ERROR_ALREADY_EXISTS);
		KB_FATAL(L"You can only have 1 instance of this program running. Please close any other instances.");
	}

	const auto cmdLines = CommandLine::GetCommandLines(argc, argv);
	const auto enableDeviceMonitorMode = ShouldEnableDMM(cmdLines);
	const auto debugLogLevelConfigured = AppConsole().CanLogOnLevel(LogLevel::Debug);
	const auto enableHiddenMode = CommandLine::Contains(L"--hide", cmdLines);
	const auto displayModelIdOnly = CommandLine::Contains(L"--model", cmdLines);

	auto pModelIdentifier = CreateModelIdentifier(USE_LEGACY_MODEL_RETRIEVER, USE_DEBUGGABLE_HOST);
	KB_INFO(L"Detected Model ID: 0x%08X", pModelIdentifier->GetModelID());

	if (displayModelIdOnly)
	{
		KB_PROMPT(L"\nPress ENTER to exit.");
		return ERROR_SUCCESS;
	}

	const auto hostFactoryFlags = (enableDeviceMonitorMode && debugLogLevelConfigured)
		? HostFactoryFlags::EnableDeviceMonitorMode
		: HostFactoryFlags::None;

	HostFactory hostFactory(std::move(pModelIdentifier), hostFactoryFlags);
	auto pHost = hostFactory.Create();

	if (!pHost)
	{
		KB_SET_FATAL_ERROR(ERROR_NOT_SUPPORTED);
		KB_FATAL(L"This system is not supported.\nPlease request for support using the following URL: https://github.com/DeviceIoControl/CppKeyboardColour/issues/new/choose.");
	}

	DisplayHostInformation(pHost.get());

	if (enableDeviceMonitorMode && debugLogLevelConfigured)
	{
		KB_WARN(L"Device monitor mode enabled! (Performance may be affected)");

		if (enableHiddenMode)
		{
			KB_WARN(L"Cannot enable hidden mode with Device monitor mode enabled.");
		}
	}

	if (enableDeviceMonitorMode && !debugLogLevelConfigured)
	{
		KB_WARN(L"Device monitor mode is not configured correctly! Fallback to default mode.");
	}

	if (!CommandLine::ExclusiveContains({ L"theme", L"inbuilt", L"backlight", L"colour", L"colours", L"lightbar" }, cmdLines))
	{
		KB_SET_FATAL_ERROR(ERROR_INVALID_PARAMETER);
		KB_FATAL(L"Invalid command line. Command is: CLEVO_KeyboardColour.exe theme/inbuilt/backlight/lightbar/colour(s) [<themeName>/<hexColour>] [--once] [--speed] <speed> [--dmm] [--hide]");
	}

	EnterHiddenMode(!enableDeviceMonitorMode && enableHiddenMode);
	
	return DoCommandOperation(std::move(pHost), cmdLines);
}
