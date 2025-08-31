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

	void SendCode(uint32_t code) override;
	void SetColour(uint8_t r, uint8_t g, uint8_t b, Zone zone) override;
	void SetBacklightOff() override;

	// Turns the keyboard backlight to its default colour (which is blue for all CLEVO laptops)
	void SetBacklightOn() override;
	void PlayAnimation(IAnimation& animation, bool bShouldLoop = true) override;

	KeyboardType GetKBType() const;

	~Keyboard() = default;

private:
	KeyboardType m_kbType;
	IKeyboardCommunicatorPtr m_ptrKbComms{};

	void Animate(IAnimation& animation);
};
