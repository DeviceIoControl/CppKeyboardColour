// Created by DeviceIoControl

#pragma once
#include "FrameCollection.h"

class FramePatternGenerator
{
public:
	FramePatternGenerator() = default;

	FrameCollection GenerateBreathe(DeviceMask devices, const Colour& targetColour, uint32_t steps, uint32_t stepTimeMs);
	FrameCollection GenerateColourBlend(DeviceMask devices, const Colour& startColour, const Colour& endColour, uint32_t steps, uint32_t stepTimeMs);
	FrameCollection GenerateAscendingPattern(DeviceMask devices, const Colour& targetColour, uint32_t steps, uint32_t stepTimeMs);
	FrameCollection GenerateDescendingPattern(DeviceMask devices, const Colour& targetColour, uint32_t steps, uint32_t stepTimeMs);
	FrameCollection GenerateBlink(DeviceMask devices, const Colour& targetColour, uint32_t blinkTimeMs);
	FrameCollection GeneratePulse(DeviceMask devices, const Colour& targetColour, uint32_t beatTimeMs);
	FrameCollection GenerateColourBlendRotation(DeviceMask devices, const Colours& startColours, const Colours& endColours, uint32_t steps, uint32_t stepTimeMs);
	FrameCollection GenerateColourWavePattern(DeviceMask devices, const Colour& targetColour, uint32_t steps, uint32_t stepTimeMs);

	~FramePatternGenerator() = default;

private:
	FrameCollection DoGenerateColourBlend(DeviceMask devices, Zone zone, const Colour& startColour, const Colour& endColour, uint32_t steps, uint32_t stepTimeMs);
	FrameCollection DoGenerateBreathePattern(DeviceMask devices, Zone zone, const Colour& targetColour, uint32_t steps, uint32_t stepTimeMs);
};