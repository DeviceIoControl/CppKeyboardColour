// Created by DeviceIoControl

#pragma once

#include "Frame.h"
#include "IAnimation.h"
#include "FrameCollection.h"

class FreshBreatheAnimation 
	: public IAnimation
{
public:
	FreshBreatheAnimation();

	std::wstring GetName() const override;

	std::optional<Frame> GetFrame(uint32_t idx) override;

	bool IsSupportedKB(KeyboardType kbType) const override;

	uint32_t Size() const override;

	~FreshBreatheAnimation() override = default;

private:
	FrameCollection m_frames;

	void AddFrame(const Frame& frame) override;

	void GenerateBreathe(const Colour& targetColour, uint32_t steps, uint32_t stepTimeMs);
};