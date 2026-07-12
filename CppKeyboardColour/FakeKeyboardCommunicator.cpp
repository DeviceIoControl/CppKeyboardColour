// Created by DeviceIoControl

#include "stdafx.h"
#include "FakeKeyboardCommunicator.h"

namespace 
{
	std::ostream& operator<<(std::ostream& _Ostr, Zone zone) 
	{
		switch (zone)
		{
		case Zone::LEFT:
			return _Ostr << "Left";

		case Zone::MID:
			return _Ostr << "Middle";

		case Zone::RIGHT:
			return _Ostr << "Right";

		case Zone::LIGHTBAR:
			return _Ostr << "Lightbar";
		}
	}

} // namespace

bool FakeKeyboardCommunicator::SendKBCode(uint32_t code)
{
	std::cout << "Code: 0x" << (void*)code << "\n";
	return true;
}

bool FakeKeyboardCommunicator::SetKBColour(Zone zone, const Colour& colour)
{
	if (zone == Zone::LIGHTBAR) 
	{
		return false;
	}

	std::cout << "Zone: " << zone << ", Colour: "
			  << "(RED - 0x" << (void*)colour[INDEX_COLOUR_RED] << "), "
			  << "(GREEN - 0x" << (void*)colour[INDEX_COLOUR_GREEN] << "), "
			  << "(BLUE - 0x" << (void*)colour[INDEX_COLOUR_BLUE] << ") \n\n";

	return true;
}

bool FakeKeyboardCommunicator::SetLightbarColour(const Colour& colour) 
{
	std::cout << "Zone: Lightbar, Colour: "
		<< "(RED - 0x" << (void*)colour[INDEX_COLOUR_RED] << "), "
		<< "(GREEN - 0x" << (void*)colour[INDEX_COLOUR_GREEN] << "), "
		<< "(BLUE - 0x" << (void*)colour[INDEX_COLOUR_BLUE] << ") \n\n";

	return true;
}
