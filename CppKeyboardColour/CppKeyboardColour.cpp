// Created by DeviceIoControl

#include "stdafx.h"

#include "Test.h"
#include "Keyboard.h"
#include "Animations.h"
#include "ServiceMain.h"

#pragma warning(disable: 4995)

int main(int argc, const char* argv[])
{
	// Test();

	// SERVICE_TABLE_ENTRYW svcTableEntry{};
	// svcTableEntry.lpServiceName = g_strServiceName.data();
	// svcTableEntry.lpServiceProc = ServiceMain;
	// 
	// StartServiceCtrlDispatcherW(&svcTableEntry);
	
	Keyboard keyboard;

	BreatheAnimation animation1;
	ColourShiftAnimation animation2;

	keyboard.PlayAnimation(animation2, true);

	return 0;
}

