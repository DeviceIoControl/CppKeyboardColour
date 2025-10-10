// Edited by BenRango
#include "stdafx.h"
#include "ColourFactory.h"
#include "ColourTransformAnimation.h"

constexpr size_t STEPS = 40.0f;
constexpr size_t FRAME_DURATION_MS = 2;

ColourTransformAnimation::ColourTransformAnimation()
{
	ColourFactory factory{};

	const auto red = factory.Create(255, 0, 0);
	const auto orange = factory.Create(255, 165, 0);
	const auto yellow = factory.Create(255, 255, 0);
	const auto green = factory.Create(0, 255, 0);
	const auto cyan = factory.Create(0, 255, 255);
	const auto blue = factory.Create(0, 0, 255);
	const auto indigo = factory.Create(75, 0, 130);
	const auto magenta = factory.Create(255, 0, 255);
	const auto pink = factory.Create(255, 192, 203);
	const auto white = factory.Create(255, 255, 255);
	const auto gray = factory.Create(128, 128, 128);

	// Creating a continuous, looping colour transition
	this->GenerateColourTransform(red, orange, STEPS, FRAME_DURATION_MS);
	this->GenerateColourTransform(orange, yellow, STEPS, FRAME_DURATION_MS);
	this->GenerateColourTransform(yellow, green, STEPS, FRAME_DURATION_MS);
	this->GenerateColourTransform(green, cyan, STEPS, FRAME_DURATION_MS);
	this->GenerateColourTransform(cyan, blue, STEPS, FRAME_DURATION_MS);
	this->GenerateColourTransform(blue, indigo, STEPS, FRAME_DURATION_MS);
	this->GenerateColourTransform(indigo, magenta, STEPS, FRAME_DURATION_MS);
	this->GenerateColourTransform(magenta, pink, STEPS, FRAME_DURATION_MS);
	this->GenerateColourTransform(pink, white, STEPS, FRAME_DURATION_MS);
	this->GenerateColourTransform(white, gray, STEPS, FRAME_DURATION_MS);
	this->GenerateColourTransform(gray, red, STEPS, FRAME_DURATION_MS);
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

		Frame currentFrame(Zone::ALL, currentColour, stepTimeMs);
		m_frames.AddFrame(currentFrame);
	}
}