// Created by DeviceIoControl

#include "stdafx.h"
#include "FramePatternGenerator.h"
#include "ColourFactory.h"
#include "MathConstants.h"

FrameCollection FramePatternGenerator::GenerateAscendingPattern(DeviceMask devices, const Colour& targetColour, uint32_t steps, uint32_t stepTimeMs)
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

		frames.AddFrame(devices, Zone::ALL, currentColour, stepTimeMs);
	}

	return frames;
}

FrameCollection FramePatternGenerator::GenerateDescendingPattern(DeviceMask devices, const Colour& targetColour, uint32_t steps, uint32_t stepTimeMs)
{
	FrameCollection frames{};

	for (size_t i = steps; i > 0; --i)
	{
		Colour currentColour{};
		const auto channelBrightness = (90.0f / steps) * i;

		for (size_t channel = 0; channel < targetColour.size(); ++channel)
		{
			currentColour[channel] = targetColour[channel] * std::sin(channelBrightness * (MATH_PI / 180.0f));
		}

		frames.AddFrame(devices, Zone::ALL, currentColour, stepTimeMs);
	}

	return frames;
}

FrameCollection FramePatternGenerator::GenerateBreathe(DeviceMask devices, const Colour& targetColour, uint32_t steps, uint32_t stepTimeMs)
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

		frames.AddFrame(devices, Zone::ALL, currentColour, stepTimeMs);
	}

	return frames;
}

FrameCollection FramePatternGenerator::GenerateColourBlend(DeviceMask devices, const Colour& startColour, const Colour& endColour, uint32_t steps, uint32_t stepTimeMs)
{
	FrameCollection frames{};

	for (size_t i = 0; i < steps; ++i)
	{
		Colour currentColour{};

		for (size_t channel = 0; channel < startColour.size(); ++channel)
		{
			currentColour[channel] = static_cast<uint8_t>(xstd::lerp(startColour[channel], endColour[channel], (1.0f / steps) * i));
		}

		frames.AddFrame(devices, Zone::ALL, currentColour, stepTimeMs);
	}

	return frames;
}

FrameCollection FramePatternGenerator::GenerateBlink(DeviceMask devices, const Colour& targetColour, uint32_t blinkTimeMs)
{
	FrameCollection frames{};
	Colour const blankColour{};

	frames.AddFrame(devices, Zone::ALL, blankColour, 1000);
	frames.AddFrame(devices, Zone::ALL, targetColour, blinkTimeMs);
	frames.AddFrame(devices, Zone::ALL, blankColour, 1000);

	return frames;
}

FrameCollection FramePatternGenerator::GeneratePulse(DeviceMask devices, const Colour& targetColour, uint32_t beatTimeMs)
{
	Colour blankColour{};
	ColourFactory factory{};
	FrameCollection frames{};

	auto const firstPulseColour = factory.Create(
		static_cast<uint8_t>(targetColour[INDEX_COLOUR_RED] * 0.33f),
		static_cast<uint8_t>(targetColour[INDEX_COLOUR_GREEN] * 0.33f),
		static_cast<uint8_t>(targetColour[INDEX_COLOUR_BLUE] * 0.33f)
	);

	frames.AddFrame(devices, Zone::ALL, blankColour, 1250); // Blank Frame
	frames.AddFrame(devices, Zone::ALL, firstPulseColour, beatTimeMs); // 1st pulse
	frames.AddFrame(devices, Zone::ALL, blankColour, beatTimeMs / 2); // Blank frame
	frames.AddFrame(devices, Zone::ALL, targetColour, beatTimeMs); // 2nd pulse
	frames.AddFrame(devices, Zone::ALL, blankColour, beatTimeMs / 2); // Blank frame

	return frames;
}