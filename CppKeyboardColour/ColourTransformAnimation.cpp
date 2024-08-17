#include "stdafx.h"
#include "ColourTransformAnimation.h"

constexpr size_t STEPS = 40.0f;
constexpr size_t FRAME_DURATION_MS = 25;

ColourTransformAnimation::ColourTransformAnimation()
{
	const auto red = CreateColour(255, 0, 0);
	const auto green = CreateColour(0, 255, 0);
	const auto blue = CreateColour(0, 0, 255);

	this->GenerateColourTransform(red, green, STEPS, FRAME_DURATION_MS);
	this->GenerateColourTransform(green, blue, STEPS, FRAME_DURATION_MS);
	this->GenerateColourTransform(blue, red, STEPS, FRAME_DURATION_MS);
}

void ColourTransformAnimation::AddFrame(const Frame& frame) 
{
	return m_frames.AddFrame(frame);
}

std::optional<Frame> ColourTransformAnimation::GetFrame(uint32_t idx)
{
	return m_frames.GetFrame(idx);
}

bool ColourTransformAnimation::IsSupportedKB(KeyboardType kbType) const 
{
	return kbType != KeyboardType::PER_KEY && kbType != KeyboardType::NONE;
}

uint32_t ColourTransformAnimation::Size() const 
{
	return m_frames.Size();
}

Colour ColourTransformAnimation::CreateColour(uint8_t r, uint8_t g, uint8_t b) const
{
	Colour colour{};

	colour[INDEX_COLOUR_RED] = r;
	colour[INDEX_COLOUR_GREEN] = g;
	colour[INDEX_COLOUR_BLUE] = b;

	return colour;
}

size_t ColourTransformAnimation::CalculateDifference(size_t a, size_t b) const
{
	return std::max(a, b) - std::min(a, b);
}

void ColourTransformAnimation::GenerateColourTransform(const Colour& startColour, const Colour& endColour, uint32_t steps, uint32_t stepTimeMs)
{
	for (size_t i = 0; i < steps; ++i)
	{
		Colour currentColour{};

		for (size_t channel = 0; channel < startColour.size(); ++channel)
		{
			size_t difference = CalculateDifference(startColour[channel], endColour[channel]);

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

		Frame currentFrame(Zone::ALL, currentColour, stepTimeMs);
		m_frames.AddFrame(currentFrame);
	}
}
