// Created by DeviceIoControl

#include "stdafx.h"

#include "Test.h"
#include "Keyboard.h"
#include "Animations.h"
#include "ServiceMain.h"
#include "CommandLine.h"

#pragma warning(disable: 4995)

int wmain(int argc, const wchar_t* argv[])
{
	//
	// SERVICE_TABLE_ENTRYW svcTableEntry{};
	// svcTableEntry.lpServiceName = g_strServiceName.data();
	// svcTableEntry.lpServiceProc = ServiceMain;
	// 
	// StartServiceCtrlDispatcherW(&svcTableEntry);
	//
	Keyboard keyboard;
	const auto cmdLines = CommandLine::GetCommandLines(argc, argv);

	std::unique_ptr<IAnimation> pAnimation{};

	if (!CommandLine::Contains(L"theme", cmdLines)) 
	{
		std::cout << "Invalid command line. Command is: KeyboardColour.exe theme [themeName]\n";
		return ERROR_INVALID_PARAMETER;
	}
	
	if (CommandLine::Contains(L"breathe", cmdLines)) 
	{
		pAnimation = std::make_unique<BreatheAnimation>();
	}
	else if (CommandLine::Contains(L"colourshift", cmdLines))
	{
		pAnimation = std::make_unique<ColourShiftAnimation>();
	}
	else if (CommandLine::Contains(L"newcolourbreathe", cmdLines)) 
	{
		pAnimation = std::make_unique<BreatheAnimationNewColours>();
	}
	else if (CommandLine::Contains(L"colourtransform", cmdLines)) 
	{
		pAnimation = std::make_unique<ColourTransformAnimation>();
	}
	else if (CommandLine::Contains(L"blink", cmdLines)) 
	{
		pAnimation = std::make_unique<PulsatingBlinkAnimation>();
	}

	if (pAnimation)
	{
		keyboard.PlayAnimation(*pAnimation, true);
	}
	else 
	{
		std::cout << "No animation was provided. Exiting...\n";
	}
	
	return 0;
}
