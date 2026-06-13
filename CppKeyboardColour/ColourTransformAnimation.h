// Created by DeviceIoControl

#pragma once

#include "IAnimation.h"
#include "FrameCollection.h"
#include "FramePatternGenerator.h"
#include "Colour.h"

class ColourTransformAnimation  
	: public IAnimation
{
public:
	ColourTransformAnimation();

	std::wstring GetName() const override;

	std::optional<Frame> GetFrame(uint32_t idx) override;

	bool IsSupportedKB(KeyboardType kbType) const override;

	uint32_t Size() const override;

	~ColourTransformAnimation() override = default;

private:
	FrameCollection m_frames{};
	FramePatternGenerator m_patternGenerator{};

	void AddFrame(const Frame& frame) override;
};
