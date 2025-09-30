#include "stdafx.h"
#include "MathConstants.h"
#include "SingleColourBreatheAnimation.h"
#include "ColourFactory.h"

constexpr size_t STEPS = 40.0f;
constexpr size_t FRAME_DURATION_MS = 45;

SingleColourBreatheAnimation::SingleColourBreatheAnimation(const Colour& targetColour)
{
	GenerateBreathe(targetColour, STEPS, FRAME_DURATION_MS);
}

std::wstring SingleColourBreatheAnimation::GetName() const
{
	return L"Single Colour Breathe";
}

std::optional<Frame> SingleColourBreatheAnimation::GetFrame(uint32_t idx)
{
	return m_frames.GetFrame(idx);
}

bool SingleColourBreatheAnimation::IsSupportedKB(KeyboardType kbType) const
{
	return (kbType != KeyboardType::PER_KEY && kbType != KeyboardType::NONE);
}

uint32_t SingleColourBreatheAnimation::Size() const
{
	return m_frames.Size();
}

void SingleColourBreatheAnimation::AddFrame(const Frame& frame)
{
	m_frames.AddFrame(frame);
}

void SingleColourBreatheAnimation::GenerateBreathe(const Colour& targetColour, uint32_t steps, uint32_t stepTimeMs)
{
	// Fade in
	for (size_t i = 0; i < steps; ++i)
	{
		Colour currentColour{};
		const auto channelBrightness = (180.0f / steps) * i;

		for (size_t channel = 0; channel < targetColour.size(); ++channel)
		{
			currentColour[channel] = targetColour[channel] * std::sin(channelBrightness * (MATH_PI / 180.0f));
		}

		Frame frame(Zone::ALL, currentColour, stepTimeMs);
		this->AddFrame(frame);
	}

	// Fade out
	for (size_t i = steps; i > 0; --i)
	{
		Colour currentColour{};
		const auto channelBrightness = (180.0f / steps) * i;

		for (size_t channel = 0; channel < targetColour.size(); ++channel)
		{
			currentColour[channel] = targetColour[channel] * std::sin(channelBrightness * (MATH_PI / 180.0f));
		}

		Frame frame(Zone::ALL, currentColour, stepTimeMs);
		this->AddFrame(frame);
	}
}