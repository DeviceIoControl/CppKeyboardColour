// Created by DeviceIoControl

#pragma once

#include "Frame.h"
#include "FrameCollection.h"
#include "FramePatternGenerator.h"
#include "IAnimation.h"
#include "Host.h"

class BreatheAnimation
	: public IAnimation
{
public:
	BreatheAnimation();

	std::wstring GetName() const override;

	std::optional<Frame> GetFrame(uint32_t idx) override;

	bool IsHostSupported(const IHost* pHost) const override;

	uint32_t Size() const override;

	~BreatheAnimation() override = default;

private:
	FrameCollection m_frames;
	FramePatternGenerator m_patternGenerator{};
};