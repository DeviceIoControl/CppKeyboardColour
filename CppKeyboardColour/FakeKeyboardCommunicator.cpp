// Created by DeviceIoControl

#include "stdafx.h"
#include "FakeKeyboardCommunicator.h"

bool FakeKeyboardCommunicator::SendKeyboardData(uint32_t data)
{
	std::cout << "Data: 0x" << (void*)data << "\n";
	return true;
}

bool FakeKeyboardCommunicator::SetKeyboardColour(Zone zone, const Colour& colour)
{
	std::cout << "Zone: 0x" << (void*)zone << ", Colour: "
		<< "(RED - 0x" << (void*)colour[INDEX_COLOUR_RED] << "), "
		<< "(GREEN - 0x" << (void*)colour[INDEX_COLOUR_GREEN] << "), "
		<< "(BLUE - 0x" << (void*)colour[INDEX_COLOUR_BLUE] << ") \n\n";

	return true;
}