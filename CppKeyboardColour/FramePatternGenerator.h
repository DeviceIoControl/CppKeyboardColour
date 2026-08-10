// Created by DeviceIoControl

#pragma once
#include "FrameCollection.h"

class FramePatternGenerator
{
public:
	FramePatternGenerator() = default;

	FrameCollection GenerateBreathe(DeviceMask devices, const Colour& targetColour, uint32_t steps, uint32_t stepTimeMs);
	FrameCollection GenerateColourTransform(DeviceMask devices, const Colour& startColour, const Colour& endColour, uint32_t steps, uint32_t stepTimeMs);
	FrameCollection GenerateAscendingPattern(DeviceMask devices, const Colour& targetColour, uint32_t steps, uint32_t stepTimeMs);
	FrameCollection GenerateDescendingPattern(DeviceMask devices, const Colour& targetColour, uint32_t steps, uint32_t stepTimeMs);
	FrameCollection GenerateBlink(DeviceMask devices, const Colour& targetColour, uint32_t blinkTimeMs);
	FrameCollection GeneratePulse(DeviceMask devices, const Colour& targetColour, uint32_t beatTimeMs);

	~FramePatternGenerator() = default;

private:
	size_t CalculateDifference(size_t a, size_t b) const;
};