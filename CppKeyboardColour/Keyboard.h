#pragma once
#include <wbemidl.h>

enum Zone : byte
{
	LEFT,
	MID,
	RIGHT,
	ALL
};

class Keyboard
{
public:
	Keyboard();
	void SetColour(byte r, byte g, byte b, Zone zone);
	~Keyboard();

private:
	IWbemClassObject* m_ClevoGetObj;
	IWbemClassObject* m_InOutParamaters[2];
	IWbemServices* m_WbemServices;
	IWbemLocator* m_WbemLocator;
};
