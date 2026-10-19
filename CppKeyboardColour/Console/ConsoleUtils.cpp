// Created by DeviceIoControl

#include "stdafx.h"
#include "ConsoleUtils.h"

std::unique_ptr<Console> g_Console = nullptr;

Console& AppConsole()
{
	if (!g_Console)
	{
		g_Console = std::make_unique<Console>();
	}

	return *g_Console;
}

void EnterHiddenMode(bool shouldHide)
{
	shouldHide ? AppConsole().Hide() : AppConsole().Show();
}
