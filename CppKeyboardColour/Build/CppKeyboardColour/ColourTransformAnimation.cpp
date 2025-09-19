// Created by DeviceIoControl

#include "stdafx.h"
#include "ColourFactory.h"
#include "ColourTransformAnimation.h"
 
constexpr size_t STEPS = 40;
constexpr size_t FRAME_DURATION_MS = 25;

ColourTransformAnimation::ColourTransformAnimation()
{
	ColourFactory factory{};

	const auto red = factory.Create(255, 0, 0);
	const auto green = factory.Create(0, 255, 0);
	const auto blue = factory.Create(0, 0, 255);

	// Transform Red -> Green
	this->GenerateColourTransform(red, green, STEPS, FRAME_DURATION_MS);

	// Transform Green -> Blue
	this->GenerateColourTransform(green, blue, STEPS, FRAME_DURATION_MS);

	// Transform Blue -> Red
	this->GenerateColourTransform(blue, red, STEPS, FRAME_DURATION_MS);
}

std::wstring ColourTransformAnimation::GetName() const 
{
	return L"Colour Transform";
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

		const Frame currentFrame(Zone::ALL, currentColour, stepTimeMs);
		m_frames.AddFrame(currentFrame);
	}
}
