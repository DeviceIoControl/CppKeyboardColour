// Created by DeviceIoControl

#pragma once

#include "Frame.h"
#include "IAnimation.h"
#include "FrameCollection.h"

class BreatheAnimationNewColours 
	: public IAnimation
{
public:
	BreatheAnimationNewColours();

	std::optional<Frame> GetFrame(uint32_t idx) override;

	bool IsSupportedKB(KeyboardType kbType) const override;

	uint32_t Size() const override;

	~BreatheAnimationNewColours() override = default;

private:
	FrameCollection m_frames;

	void AddFrame(const Frame& frame) override;

	Colour CreateColour(uint8_t red, uint8_t green, uint8_t blue);
	void GenerateBreathe(const Colour& targetColour, uint32_t steps, uint32_t stepTimeMs);
};