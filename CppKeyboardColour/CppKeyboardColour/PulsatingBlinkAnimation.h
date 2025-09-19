// Created by DeviceIoControl

#pragma once

#include "Colour.h"
#include "IAnimation.h"
#include "FrameCollection.h"

//
// Effect Name: Pulsating Blink
// 
// Description:
// 
// The pulsating blink effect aims to create a dynamic and attention - grabbing display by alternating between bright and dim states.Here are the specifics of how I envision this effect :
// 
// Cycle Pattern:
// Start with the zone at full brightness for a brief moment (approximately 0.2 seconds), 
// then quickly fade it to a dim state (approximately 10 % brightness) over the next 0.3 seconds.
// 
// After reaching the dim state, maintain it for about 2 seconds before repeating the cycle.
// 
// Smooth Transitions:
// Ensure that transitions between brightness levels are smooth and abrupt, creating a noticeable blink effect.
//

class PulsatingBlinkAnimation 
	: public IAnimation
{
public:
	PulsatingBlinkAnimation();
	~PulsatingBlinkAnimation() = default;

	std::wstring GetName() const override;

	std::optional<Frame> GetFrame(uint32_t idx) override;

	bool IsSupportedKB(KeyboardType kbType) const override;

	uint32_t Size() const override;
	

private:
	FrameCollection m_frames{};

	void AddFrame(const Frame& frame) override;

	void GenerateBlink(const Colour& targetColour, uint32_t blinkTimeMs);
};