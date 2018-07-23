#pragma once
// Created by DeviceIoControl

#include <wbemidl.h>
#include "Animation.h"
#include "Animation.cpp"

//Animations that are built-in to the computer... (Therefore NO CPU USAGE when using these!)
enum SystemAnimation : unsigned int
{
	KB_MODE_WAVE = 0xB0000000, //Works but, shuts off fans for some reason until you PRESS 'Fn + F1'...
	KB_MODE_CYCLE = 0x33010000,
	KB_MODE_DANCE = 0x80000000,
	KB_MODE_FLASH = 0xA0000000, //Works but, shuts off fans for some reason until you PRESS 'Fn + F1'...
	KB_MODE_TEMPO = 0x90000000, //Works but, shuts off fans for some reason until you PRESS 'Fn + F1'...
	KB_MODE_CUSTOM = 0x00000000,
	KB_MODE_BREATHE = 0x1002A000, //Works but, shuts off fans for some reason until you PRESS 'Fn + F1'...
	KB_MODE_RANDOM_COLOUR = 0x70000000  //Works but, shuts off fans for some reason until you PRESS 'Fn + F1'...
};

class Keyboard
{
public:
	Keyboard();
	void SetColour(byte r, byte g, byte b, Zone zone);
	void SysAnimation(SystemAnimation animation);

	template<unsigned int size>
	void PlayAnimation(const Animation<size>* const pAnimation)
	{
		unsigned int actualSize = (!size) ? pAnimation->size() : size;

		for (int i = 0; i < actualSize; ++i) {

			for (int y = 0; y < 3; ++y) {

				Keyboard::SetColour(pAnimation->getFrame(i).colour[y].rgb[0],
					pAnimation->getFrame(i).colour[y].rgb[1],
					pAnimation->getFrame(i).colour[y].rgb[2],
					pAnimation->getFrame(i).colour[y].zone);

				if (pAnimation->getFrame(i).colour[y].zone == Zone::ALL) { break; }
			}

			Sleep(pAnimation->getFrame(i).ms_time);
		}
	}

	~Keyboard();

private:
	IWbemClassObject* m_ClevoGetObj;
	IWbemClassObject* m_InOutParamaters[2];
	IWbemServices* m_WbemServices;
	IWbemLocator* m_WbemLocator;
};
