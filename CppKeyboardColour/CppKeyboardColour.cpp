// CppKeyboardColour.cpp : Defines the entry point for the console application.
// Created by DeviceIoControl

#include "stdafx.h"

#include "Test.h"
#include "Keyboard.h"
#include "ColourShiftAnimation.h"

#include "ServiceMain.h"

#pragma warning(disable: 4995)

int main(int argc, const char* argv[])
{
	Test();

	SERVICE_TABLE_ENTRYW svcTableEntry{};
	svcTableEntry.lpServiceName = g_strServiceName.data();
	svcTableEntry.lpServiceProc = ServiceMain;

	StartServiceCtrlDispatcherW(&svcTableEntry);

	Keyboard keyboard;
	ColourShiftAnimation animation;
	keyboard.PlayAnimation(animation, true);

	return 0;
}

