// Created by DeviceIoControl

#pragma once

#include "IKeyboard.h"
#include "IAnimation.h"
#include "SystemAnimation.h"
#include "IKeyboardCommunicator.h"

class Keyboard 
	: public IKeyboard
{
public:
	Keyboard();

	void SetColour(uint8_t r, uint8_t g, uint8_t b, Zone zone) override;
	void SysAnimation(SystemAnimation animation) override;
	void PlayAnimation(IAnimation& animation, bool bShouldLoop = true) override;

	KeyboardType GetKBType() const;

	~Keyboard() = default;

private:
	KeyboardType m_kbType;
	IKeyboardCommunicatorPtr m_ptrKbComms{};

	void Animate(IAnimation& animation);
};
