// Created by DeviceIoControl

#pragma once

#include "IAnimation.h"
#include "FrameCollection.h"
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

	void AddFrame(const Frame& frame) override;

	FrameCollection m_frames{};

	size_t CalculateDifference(size_t a, size_t b) const;

	void GenerateColourTransform(const Colour& startColour, const Colour& endColour, uint32_t steps, uint32_t stepTimeMs);
};
