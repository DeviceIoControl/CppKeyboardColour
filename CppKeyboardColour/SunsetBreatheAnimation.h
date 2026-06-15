// Created by DeviceIoControl

#pragma once

#include "IAnimation.h"
#include "FrameCollection.h"
#include "FramePatternGenerator.h"

class SunsetBreatheAnimation
	: public IAnimation
{
public:
	SunsetBreatheAnimation();

	std::wstring GetName() const override;

	std::optional<Frame> GetFrame(uint32_t idx) override;

	bool IsSupportedKB(KeyboardType kbType) const override;

	uint32_t Size() const override;

	~SunsetBreatheAnimation() override = default;
	
private:
	FrameCollection m_frames{};
	FramePatternGenerator m_patternGenerator{};
};