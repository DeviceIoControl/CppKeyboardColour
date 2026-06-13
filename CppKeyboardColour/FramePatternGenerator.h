#pragma once
#include "FrameCollection.h"

class FramePatternGenerator
{
public:
	FramePatternGenerator();

	FrameCollection GenerateBreathe(const Colour& targetColour, uint32_t steps, uint32_t stepTimeMs);
	FrameCollection GenerateColourTransform(const Colour& startColour, const Colour& endColour, uint32_t steps, uint32_t stepTimeMs);
	FrameCollection GenerateAscendingPattern(const Colour& targetColour, uint32_t steps, uint32_t stepTimeMs);
	FrameCollection GenerateDescendingPattern(const Colour& startColour, uint32_t steps, uint32_t stepTimeMs);

	~FramePatternGenerator() = default;

private:
	size_t CalculateDifference(size_t a, size_t b) const;
};