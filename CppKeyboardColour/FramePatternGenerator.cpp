// Created by DeviceIoControl

#include "stdafx.h"
#include "FramePatternGenerator.h"
#include "MathConstants.h"

FramePatternGenerator::FramePatternGenerator()
{
}

size_t FramePatternGenerator::CalculateDifference(size_t a, size_t b) const
{
	return std::max(a, b) - std::min(a, b);
}

FrameCollection FramePatternGenerator::GenerateAscendingPattern(const Colour& targetColour, uint32_t steps, uint32_t stepTimeMs)
{
	FrameCollection frames{};

	for (size_t i = 0; i < steps; ++i)
	{
		Colour currentColour{};
		const auto channelBrightness = (90.0f / steps) * i;

		for (size_t channel = 0; channel < targetColour.size(); ++channel)
		{
			currentColour[channel] = targetColour[channel] * std::sin(channelBrightness * (MATH_PI / 180.0f));
		}

		Frame const frame(Zone::ALL, currentColour, stepTimeMs);
		frames.AddFrame(frame);
	}

	return frames;
}

FrameCollection FramePatternGenerator::GenerateDescendingPattern(const Colour& startColour, uint32_t steps, uint32_t stepTimeMs)
{
	FrameCollection frames{};

	for (size_t i = steps; i > 0; --i)
	{
		Colour currentColour{};
		const auto channelBrightness = (90.0f / steps) * i;

		for (size_t channel = 0; channel < startColour.size(); ++channel)
		{
			currentColour[channel] = startColour[channel] * std::sin(channelBrightness * (MATH_PI / 180.0f));
		}

		Frame const frame(Zone::ALL, currentColour, stepTimeMs);
		frames.AddFrame(frame);
	}

	return frames;
}

FrameCollection FramePatternGenerator::GenerateBreathe(const Colour& targetColour, uint32_t steps, uint32_t stepTimeMs)
{
	FrameCollection frames{};

	for (size_t i = 0; i < steps; ++i)
	{
		Colour currentColour{};
		const auto channelBrightness = (180.0f / steps) * i;

		for (size_t channel = 0; channel < targetColour.size(); ++channel)
		{
			currentColour[channel] = targetColour[channel] * std::sin(channelBrightness * (MATH_PI / 180.0f));
		}

		Frame const frame(Zone::ALL, currentColour, stepTimeMs);
		frames.AddFrame(frame);
	}

	return frames;
}

FrameCollection FramePatternGenerator::GenerateColourTransform(const Colour& startColour, const Colour& endColour, uint32_t steps, uint32_t stepTimeMs)
{
	FrameCollection frames{};

	for (size_t i = 0; i < steps; ++i)
	{
		Colour currentColour{};

		for (size_t channel = 0; channel < startColour.size(); ++channel)
		{
			size_t const difference = CalculateDifference(startColour[channel], endColour[channel]);

			if (startColour[channel] < endColour[channel])
			{
				currentColour[channel] = startColour[channel] + ((difference / steps) * i);
				continue;
			}

			if (startColour[channel] > endColour[channel])
			{
				currentColour[channel] = startColour[channel] - ((difference / steps) * i);
				continue;
			}

			currentColour[channel] = endColour[channel];
		}

		const Frame currentFrame(Zone::ALL, currentColour, stepTimeMs);
		frames.AddFrame(currentFrame);
	}

	return frames;
}
