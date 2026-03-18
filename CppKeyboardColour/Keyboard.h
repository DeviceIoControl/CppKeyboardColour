// Created by DeviceIoControl

#pragma once

#include "IKeyboard.h"
#include "IAnimation.h"
#include "ColourFactory.h"
#include "IKeyboardCommunicator.h"

class Keyboard 
	: public IKeyboard
{
public:
	Keyboard(KeyboardType kbType, IKeyboardCommunicatorPtr ptrKbComms);

	void SendCode(uint32_t code) override;
	void SetColour(uint8_t r, uint8_t g, uint8_t b, Zone zone) override;

	// Turns the keyboard backlight to its default colour (which is blue for all CLEVO laptops)
	void SetBacklightOn() override;
	void SetBacklightOff() override;
	void PlayAnimation(IAnimation& animation, bool bShouldLoop) override;

	KeyboardType GetKBType() const;

	~Keyboard() = default;

private:
	KeyboardType m_kbType;
	ColourFactory m_colourFactory{};
	IKeyboardCommunicatorPtr m_ptrKbComms{};

	void Animate(IAnimation& animation);
};
