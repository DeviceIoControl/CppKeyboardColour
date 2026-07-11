// Created by DeviceIoControl

#pragma once

#include "IKeyboard.h"
#include "IAnimation.h"
#include "ColourFactory.h"
#include "IKeyboardDevice.h"
#include "IKeyboardCommunicator.h"

class Keyboard 
	: public IKeyboard
{
public:
	Keyboard(std::shared_ptr<IKeyboardDevice> pKBDevice, std::shared_ptr<IKeyboardCommunicator> pKbComms);

	void SendCode(uint32_t code) override;
	void SetColour(uint8_t r, uint8_t g, uint8_t b, Zone zone) override;

	// Turns the keyboard backlight to its default colour (which is blue for all CLEVO laptops)
	void SetBacklightOn() override;
	void SetBacklightOff() override;
	void PlayAnimation(IAnimation& animation, bool bShouldLoop) override;
	bool SetSpeedFactor(float factor) override;

	KeyboardType GetKBType() const;

	~Keyboard() = default;

private:
	float m_speedFactor = 1.0f;

	ColourFactory m_colourFactory{};
	std::shared_ptr<IKeyboardDevice> m_pKBDevice{};
	std::shared_ptr<IKeyboardCommunicator> m_ptrKbComms{};

	void Animate(IAnimation& animation);
};
