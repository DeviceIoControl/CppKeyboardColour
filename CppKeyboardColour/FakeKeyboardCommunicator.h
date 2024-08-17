#pragma once

#include "stdafx.h"
#include "IKeyboardCommunicator.h"

class FakeKeyboardCommunicator 
	: public IKeyboardCommunicator
{
public:
	FakeKeyboardCommunicator() = default;

	bool SendKeyboardData(uint32_t data) override 
	{
		std::cout << "Data: 0x" << (void*)data << "\n";
		return true;
	}

	bool SetKeyboardColour(Zone zone, const Colour& colour) override 
	{
		std::cout << "Zone: 0x" << (void*)zone << ", Colour: "
			<< "(RED - 0x" << (void*)colour[INDEX_COLOUR_RED] << "), "
			<< "(GREEN - 0x" << (void*)colour[INDEX_COLOUR_GREEN] << "), "
			<< "(BLUE - 0x" << (void*)colour[INDEX_COLOUR_BLUE] << ") \n\n";

		return true;
	}

	~FakeKeyboardCommunicator() override = default;
};