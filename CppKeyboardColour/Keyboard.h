// Created by DeviceIoControl

#pragma once

#include "Animation.h"
#include "SystemAnimation.h"
#include "ScopedComPtr.h"

class Keyboard
{
public:
	Keyboard();

	void SetColour(uint8_t r, uint8_t g, uint8_t b, Zone zone);
	void SysAnimation(SystemAnimation animation);

	void PlayAnimation(Animation& animation, bool bShouldLoop = true);

	~Keyboard() = default;

private:
	ScopedComPtr<IWbemClassObject> m_pClevoGetObject;
	ScopedComPtr<IWbemClassObject> m_pDataParameter;
};
