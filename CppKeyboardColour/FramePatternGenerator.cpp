// Created by DeviceIoControl

#include "stdafx.h"
#include "FramePatternGenerator.h"
#include "ColourFactory.h"
#include "MathConstants.h"

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

		frames.AddFrame(Zone::ALL, currentColour, stepTimeMs);
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

		frames.AddFrame(Zone::ALL, currentColour, stepTimeMs);
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

		frames.AddFrame(Zone::ALL, currentColour, stepTimeMs);
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

		frames.AddFrame(Zone::ALL, currentColour, stepTimeMs);
	}

	return frames;
}

FrameCollection FramePatternGenerator::GenerateBlink(const Colour& targetColour, uint32_t blinkTimeMs) 
{
	FrameCollection frames{};
	Colour const blankColour{};

	frames.AddFrame(Zone::ALL, blankColour, 1000);
	frames.AddFrame(Zone::ALL, targetColour, blinkTimeMs);
	frames.AddFrame(Zone::ALL, blankColour, 1000);

	return frames;
}

FrameCollection FramePatternGenerator::GeneratePulse(const Colour& targetColour, uint32_t beatTimeMs) 
{
	Colour blankColour{};
	ColourFactory factory{};
	FrameCollection frames{};

	auto const firstPulseColour = factory.Create(
		static_cast<uint8_t>(targetColour[INDEX_COLOUR_RED] * 0.33f),
		static_cast<uint8_t>(targetColour[INDEX_COLOUR_GREEN] * 0.33f),
		static_cast<uint8_t>(targetColour[INDEX_COLOUR_BLUE] * 0.33f)
	);

	frames.AddFrame(Zone::ALL, blankColour, 1250); // Blank Frame
	frames.AddFrame(Zone::ALL, firstPulseColour, beatTimeMs); // 1st pulse
	frames.AddFrame(Zone::ALL, blankColour, beatTimeMs / 2); // Blank frame
	frames.AddFrame(Zone::ALL, targetColour, beatTimeMs); // 2nd pulse
	frames.AddFrame(Zone::ALL, blankColour, beatTimeMs / 2); // Blank frame

	return frames;
}