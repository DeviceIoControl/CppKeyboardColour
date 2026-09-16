// Created by DeviceIoControl

#include "stdafx.h"
#include "ConsoleUtils.h"

void WaitForEnterIfNeeded()
{
	std::cout << "\nPress Enter to exit...";
	std::getchar();
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
