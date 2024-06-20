// Created by DeviceIoControl

#include "stdafx.h"

#include "Test.h"
#include "Keyboard.h"
#include "Animations.h"
#include "ServiceMain.h"

#pragma warning(disable: 4995)

int wmain(int argc, const wchar_t* argv[])
{
	// SERVICE_TABLE_ENTRYW svcTableEntry{};
	// svcTableEntry.lpServiceName = g_strServiceName.data();
	// svcTableEntry.lpServiceProc = ServiceMain;
	// 
	// StartServiceCtrlDispatcherW(&svcTableEntry);
	
	Keyboard keyboard;

	BreatheAnimation breathe;
	ColourShiftAnimation colourShift;

	keyboard.PlayAnimation(breathe, true);

	return 0;
}
