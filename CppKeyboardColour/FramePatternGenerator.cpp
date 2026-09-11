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
		const auto channelBrightnessFactor = std::sin(((90.0f / steps) * i) * (MATH_PI / 180.0f));

		const Colour currentColour{
			(targetColour[INDEX_COLOUR_RED] * channelBrightnessFactor),
			(targetColour[INDEX_COLOUR_GREEN] * channelBrightnessFactor),
			(targetColour[INDEX_COLOUR_BLUE] * channelBrightnessFactor)
		};

		frames.AddFrame(devices, Zone::ALL, currentColour, stepTimeMs);
	}

	return frames;
}

FrameCollection FramePatternGenerator::GenerateDescendingPattern(DeviceMask devices, const Colour& targetColour, uint32_t steps, uint32_t stepTimeMs)
{
	FrameCollection frames{};

	for (size_t i = steps; i > 0; --i)
	{
		const auto channelBrightnessFactor = std::sin(((90.0f / steps) * i) * (MATH_PI / 180.0f));

		const Colour currentColour{
			(targetColour[INDEX_COLOUR_RED] * channelBrightnessFactor),
			(targetColour[INDEX_COLOUR_GREEN] * channelBrightnessFactor),
			(targetColour[INDEX_COLOUR_BLUE] * channelBrightnessFactor)
		};

		frames.AddFrame(devices, Zone::ALL, currentColour, stepTimeMs);
	}

	return frames;
}

FrameCollection FramePatternGenerator::GenerateBreathe(DeviceMask devices, const Colour& targetColour, uint32_t steps, uint32_t stepTimeMs)
{
	return this->DoGenerateBreathePattern(devices, Zone::ALL, targetColour, steps, stepTimeMs);
}

FrameCollection FramePatternGenerator::GenerateColourBlend(DeviceMask devices, const Colour& startColour, const Colour& endColour, uint32_t steps, uint32_t stepTimeMs)
{
	return this->DoGenerateColourBlend(devices, Zone::ALL, startColour, endColour, steps, stepTimeMs);
}

FrameCollection FramePatternGenerator::GenerateBlink(DeviceMask devices, const Colour& targetColour, uint32_t blinkTimeMs)
{
	FrameCollection frames{};
	const Colour blankColour{};

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

	const auto firstPulseColour = factory.Create(
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

FrameCollection FramePatternGenerator::GenerateColourBlendRotation(DeviceMask devices, const Colours& startColours, const Colours& endColours, uint32_t steps, uint32_t stepTimeMs)
{
	FrameCollection frames{};

	auto leftZoneFrames = this->DoGenerateColourBlend(devices, Zone::LEFT, startColours[ZoneToArrayIndex(Zone::LEFT)], endColours[ZoneToArrayIndex(Zone::LEFT)], steps, stepTimeMs);
	auto midZoneFrames = this->DoGenerateColourBlend(devices, Zone::MID, startColours[ZoneToArrayIndex(Zone::MID)], endColours[ZoneToArrayIndex(Zone::MID)], steps, stepTimeMs);
	auto rightZoneFrames = this->DoGenerateColourBlend(devices, Zone::RIGHT, startColours[ZoneToArrayIndex(Zone::RIGHT)], endColours[ZoneToArrayIndex(Zone::RIGHT)], steps, stepTimeMs);

	// Interleave the zoned frames to simulate a single frame with multiple individual zone colours.
	for (size_t i = 0; i < steps; ++i)
	{
		frames.TryAddFrame(leftZoneFrames.GetFrame(i));
		frames.TryAddFrame(midZoneFrames.GetFrame(i));
		frames.TryAddFrame(rightZoneFrames.GetFrame(i));
	}

	return frames;
}

FrameCollection FramePatternGenerator::DoGenerateColourBlend(DeviceMask devices, Zone zone, const Colour& startColour, const Colour& endColour, uint32_t steps, uint32_t stepTimeMs)
{
	FrameCollection frames{};

	for (size_t i = 0; i < steps; ++i)
	{
		const Colour currentColour{
			static_cast<uint8_t>(xstd::lerp(startColour[INDEX_COLOUR_RED], endColour[INDEX_COLOUR_RED], (1.0f / steps) * i)),
			static_cast<uint8_t>(xstd::lerp(startColour[INDEX_COLOUR_GREEN], endColour[INDEX_COLOUR_GREEN], (1.0f / steps) * i)),
			static_cast<uint8_t>(xstd::lerp(startColour[INDEX_COLOUR_BLUE], endColour[INDEX_COLOUR_BLUE], (1.0f / steps) * i))
		};

		frames.AddFrame(devices, zone, currentColour, stepTimeMs);
	}

	return frames;
}

FrameCollection FramePatternGenerator::DoGenerateBreathePattern(DeviceMask devices, Zone zone, const Colour& targetColour, uint32_t steps, uint32_t stepTimeMs) 
{
	FrameCollection frames{};

	for (size_t i = 0; i < steps; ++i)
	{
		const auto channelBrightnessFactor = std::sin(((180.0f / steps) * i) * (MATH_PI / 180.0f));

		const Colour currentColour{
			(targetColour[INDEX_COLOUR_RED] * channelBrightnessFactor),
			(targetColour[INDEX_COLOUR_GREEN] * channelBrightnessFactor),
			(targetColour[INDEX_COLOUR_BLUE] * channelBrightnessFactor)
		};

		frames.AddFrame(devices, zone, currentColour, stepTimeMs);
	}

	return frames;
}

FrameCollection FramePatternGenerator::GenerateColourWavePattern(DeviceMask devices, const Colour& targetColour, uint32_t steps, uint32_t stepTimeMs) 
{
	FrameCollection frames;
	
	auto leftZoneBreathe = this->DoGenerateBreathePattern(devices, Zone::LEFT, targetColour, steps, stepTimeMs);
	auto midZoneBreathe = this->DoGenerateBreathePattern(devices, Zone::MID, targetColour, steps, stepTimeMs);
	auto rightZoneBreathe = this->DoGenerateBreathePattern(devices, Zone::RIGHT, targetColour, steps, stepTimeMs);

	for (size_t i = 0; i < (steps * 1.66f); ++i)
	{
		if (i >= 0 && i <= steps)
		{
			frames.TryAddFrame(leftZoneBreathe.GetFrame(i));
		}
		
		if (i >= (steps * 0.33f) && i <= (steps * 1.33f))
		{
			frames.TryAddFrame(midZoneBreathe.GetFrame(i - static_cast<uint32_t>(steps * 0.33f)));
		}

		if (i >= (steps * 0.66f) && i <= (steps * 1.66f))
		{
			frames.TryAddFrame(rightZoneBreathe.GetFrame((i - static_cast<uint32_t>(steps * 0.66f))));
		}
	}

	return frames;
}
