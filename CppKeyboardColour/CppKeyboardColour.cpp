// Created by DeviceIoControl

#include "stdafx.h"

#include "Test.h"
#include "Keyboard.h"

#include "BreatheAnimation.h"
#include "ColourShiftAnimation.h"

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

	keyboard.PlayAnimation(animation1, true);

	return 0;
}

