// CppKeyboardColour.cpp : Defines the entry point for the console application.
// Created by DeviceIoControl

#include "stdafx.h"

#include "Keyboard.h"
#include "Animation.h"

#pragma warning(disable: 4995)

int main(int argc, const char* argv[])
{
	Keyboard keyboard;
	
	byte rgb[3][3] = 
	{
		{ 0xFF, 0x00, 0x00 },
		{ 0x00, 0xFF, 0x00 },
		{ 0x00, 0x00, 0xFF }
	};

	while (true)
	{
		std::cout << "Changing Zone colours...\n";
		for (int i = 0; i < 0xFF; ++i) {

			for (int y = 0; y < 3; ++y) 
			{
				keyboard.SetColour(rgb[y][0], rgb[y][1], rgb[y][2], (Zone)y);
				rgb[y][y]--;
				rgb[y][(y + 2) % 3]++;
			}
		}
		std::cout << "ZONE 1: [BLUE] " << "ZONE 2: [RED] " << "ZONE 3: [GREEN]\n\n";


		Sleep(5000);

		std::cout << "Changing Zone colours...\n";
		for (int i = 0; i < 0xFF; ++i) {

			for (int y = 0; y < 3; ++y) 
			{
				keyboard.SetColour(rgb[y][0], rgb[y][1], rgb[y][2], (Zone)y);
				rgb[y][(y + 2) % 3]--;
				rgb[y][(y + 1) % 3]++;
			}
		}
		std::cout << "ZONE 1: [GREEN] " << "ZONE 2: [BLUE] " << "ZONE 3: [RED]\n\n";

		Sleep(5000);

		std::cout << "Changing Zone colours...\n";
		for (int i = 0; i < 0xFF; ++i) {

			for (int y = 0; y < 3; ++y) 
			{
				keyboard.SetColour(rgb[y][0], rgb[y][1], rgb[y][2], (Zone)y);
				rgb[y][(y + 1) % 3]--;
				rgb[y][y]++;
			}
		}
		std::cout << "ZONE 1: [RED] " << "ZONE 2: [GREEN] " << "ZONE 3: [BLUE]\n\n";

		Sleep(5000);
	}

    return 0;
}

