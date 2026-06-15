// Created by DeviceIoControl

#include "stdafx.h"
#include "CommandLine.h"
#include "KeyboardFactory.h"
#include "SingleInstanceEvent.h"
#include "KeyboardOperationsHandler.h"
#include "ConsoleUtils.h"

#pragma warning(disable: 4995)

#define STATUS_NOT_IMPLEMENTED 0xC0000002

int wmain(int argc, const wchar_t* argv[])
{
	std::cout << "CLEVO Keyboard Colours Tool 1.26.XXXX (Test Build) - Created by DeviceIoControl.\n\n";

	if (!IsSingleInstance())
	{
		std::cout << "You can only have 1 instance of this program running. Please close any other instances.\n";
		WaitForEnterIfNeeded();
		return ERROR_ALREADY_EXISTS;
	}

	KeyboardFactory kbFactory{};
	auto ptrKeyboard = kbFactory.Create();

	if (!ptrKeyboard)
	{
		std::cout << "This system is not supported.\n\n Please request for support using the following URL: https://github.com/DeviceIoControl/CppKeyboardColour/issues/new.\n";
		WaitForEnterIfNeeded();
		return STATUS_NOT_IMPLEMENTED;
	}

	const auto cmdLines = CommandLine::GetCommandLines(argc, argv);

	if (!CommandLine::ExclusiveContains({ L"theme", L"inbuilt", L"backlight", L"colour" }, cmdLines))
	{
		std::cout << "Invalid command line. Command is: CLEVO_KeyboardColour.exe theme/inbuilt/backlight/colour [<themeName>/<hexColour>] [--once] [--speed] <speed>\n";
		WaitForEnterIfNeeded();
		return ERROR_INVALID_PARAMETER;
	}

	return DoKeyboardOperation(ptrKeyboard.get(), cmdLines);
}
