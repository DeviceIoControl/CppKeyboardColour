// Created by DeviceIoControl

#include "stdafx.h"
#include "FakeKeyboardCommunicator.h"

bool FakeKeyboardCommunicator::SendKBCode(uint32_t code)
{
	std::cout << "Code: 0x" << (void*)code << "\n";
	return true;
}

bool FakeKeyboardCommunicator::SetKBColour(Zone zone, const Colour& colour)
{
	std::cout << "Zone: 0x" << (void*)zone << ", Colour: "
			  << "(RED - 0x" << (void*)colour[INDEX_COLOUR_RED] << "), "
			  << "(GREEN - 0x" << (void*)colour[INDEX_COLOUR_GREEN] << "), "
			  << "(BLUE - 0x" << (void*)colour[INDEX_COLOUR_BLUE] << ") \n\n";

	return true;
}