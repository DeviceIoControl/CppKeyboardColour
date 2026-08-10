// Created by DeviceIoControl

#pragma once

#include "IAnimation.h"
#include "FrameCollection.h"
#include "FramePatternGenerator.h"
#include "IHost.h"

class PinkBreatheAnimation 
	: public IAnimation
{
public:
	PinkBreatheAnimation();

	std::wstring GetName() const override;

	std::optional<Frame> GetFrame(uint32_t idx) override;

	bool IsHostSupported(const IHost* pHost) const override;

	uint32_t Size() const override;

	~PinkBreatheAnimation() override = default;

private:
	FrameCollection m_frames{};
	FramePatternGenerator m_patternGenerator{};
};