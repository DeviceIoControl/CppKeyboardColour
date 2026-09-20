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

void WaitForEnterIfNeeded()
{
	AppConsole().Prompt(L"\nPress Enter to exit...");
}

void EnterHiddenMode(bool shouldHide)
{
	shouldHide ? AppConsole().Hide() : AppConsole().Show();
}

std::ostream& operator<<(std::ostream& _Ostr, DeviceMask devices)
{
	if (!!(devices & DeviceMask::Keyboard))
	{
		_Ostr << "[Keyboard] ";
	}

	if (!!(devices & DeviceMask::Lightbar))
	{
		_Ostr << "[Lightbar] ";
	}

	if (!!(devices & DeviceMask::Logo))
	{
		_Ostr << "[Logo] ";
	}

	return _Ostr;
}

std::ostream& operator<<(std::ostream& _Ostr, KeyboardType kbType)
{
	switch (kbType)
	{
	case KeyboardType::SINGLE_ZONE:
		return _Ostr << "Single Zone";

	case KeyboardType::TRIPLE_ZONE:
		return _Ostr << "Triple Zone";

	case KeyboardType::PER_KEY:
		return _Ostr << "Per-Key";
	}

	return _Ostr;
}
