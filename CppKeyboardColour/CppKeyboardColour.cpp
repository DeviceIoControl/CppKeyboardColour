// CppKeyboardColour.cpp : Defines the entry point for the console application.
// Created by DeviceIoControl

#include "stdafx.h"
#include <iostream>
#include <Windows.h>

#include "Keyboard.h"

int main(int argc, char** argv)
{
	Keyboard keyboard;
	keyboard.SysAnimation(SystemAnimation::KB_MODE_RANDOM_COLOUR);
	Animation<10> anim(0);
	keyboard.PlayAnimation<10>(&anim);

	getchar();
	return 0;
	//keyboard.SetSysAnimation(SystemAnimation::KB_MODE_BREATHE);

	byte rgb[3][3] = 
	{
		{ 0xFF, 0x00, 0x00 },
		{ 0x00, 0xFF, 0x00 },
		{ 0x00, 0x00, 0xFF }
	};

	while (true)
	{
		for (int i = 0; i < 0xFF; ++i) {

			for (int y = 0; y < 3; ++y) {
				keyboard.SetColour(rgb[y][0], rgb[y][1], rgb[y][2], (Zone)y);
				rgb[y][y]--;
				rgb[y][(y + 2) % 3]++;
			}

			//keyboard.SetColour(rgb[0][0], rgb[0][1], rgb[0][2], Zone::LEFT);
			//rgb[0][0]--;
			//rgb[0][2]++;
			//keyboard.SetColour(rgb[1][0], rgb[1][1], rgb[1][2], Zone::MID);
			//rgb[1][1]--;
			//rgb[1][0]++;
			//keyboard.SetColour(rgb[2][0], rgb[2][1], rgb[2][2], Zone::RIGHT);
			//rgb[2][2]--;
			//rgb[2][1]++;
			//Sleep(75);
		}
		Sleep(2000);

		for (int i = 0; i < 0xFF; ++i)
		{
			for (int y = 0; y < 3; ++y)
			{
				keyboard.SetColour(rgb[y][0], rgb[y][1], rgb[y][2], (Zone)y);
				rgb[y][(y + 2) % 3]--;
				rgb[y][(y + 1) % 3]++;
			}

			//keyboard.SetColour(rgb[0][0], rgb[0][1], rgb[0][2], Zone::LEFT);
			//rgb[0][2]--;
			//rgb[0][1]++;
			//keyboard.SetColour(rgb[1][0], rgb[1][1], rgb[1][2], Zone::MID);
			//rgb[1][0]--;
			//rgb[1][2]++;
			//keyboard.SetColour(rgb[2][0], rgb[2][1], rgb[2][2], Zone::RIGHT);
			//rgb[2][1]--;
			//rgb[2][0]++;
			//Sleep(75);
		}
		Sleep(2000);

		for (int i = 0; i < 0xFF; ++i) {

			for (int y = 0; y < 3; ++y)
			{
				keyboard.SetColour(rgb[y][0], rgb[y][1], rgb[y][2], (Zone)y);
				rgb[y][(y + 1) % 3]--;
				rgb[y][y]++;
			}

			//keyboard.SetColour(rgb[0][0], rgb[0][1], rgb[0][2], Zone::LEFT);
			//rgb[0][1]--;
			//rgb[0][0]++;
			//keyboard.SetColour(rgb[1][0], rgb[1][1], rgb[1][2], Zone::MID);
			//rgb[1][2]--;
			//rgb[1][1]++;
			//keyboard.SetColour(rgb[2][0], rgb[2][1], rgb[2][2], Zone::RIGHT);
			//rgb[2][0]--;
			//rgb[2][2]++;
			//Sleep(75);
		}
		Sleep(2000);
	}

    return 0;
}

