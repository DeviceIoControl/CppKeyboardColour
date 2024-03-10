// Created by DeviceIoControl

#pragma once

#include "IAnimation.h"
#include "SystemAnimation.h"
#include "ScopedComPtr.h"

class Keyboard
{
public:
	Keyboard();

	void SetColour(uint8_t r, uint8_t g, uint8_t b, Zone zone);
	void SysAnimation(SystemAnimation animation);

	void PlayAnimation(IAnimation& animation, bool bShouldLoop = true);

	~Keyboard() = default;

private:
	uint32_t m_uiDeviceId = 0;
	ScopedComPtr<IWbemClassObject> m_pClevoGetObject;
	ScopedComPtr<IWbemClassObject> m_pDataParameter;

	std::optional<uint32_t> GetDeviceID();

	void DoAnimation(IAnimation& animation);
};
