#include "stdafx.h"
#include "MathConstants.h"
#include "BreatheAnimationNewColours.h"
#include "ColourFactory.h"

//
// rgb(255 255, 0) yellow
// rgb(255, 0, 30) red
// rgb(60, 0, 255) Purple
// rgb(0, 255, 60) green
// rgb(0, 255, 120) green - Why is there duplication?
// rgb(255, 255, 255) white
// rgb(255, 0, 255) purple - Why is there duplication?
// rgb(255, 120, 120) Brown
//

constexpr size_t STEPS = 40.0f;
constexpr size_t FRAME_DURATION_MS = 25;

FreshBreatheAnimation::FreshBreatheAnimation()
{
	ColourFactory factory{};
	
	// Breathe yellow
	GenerateBreathe(factory.Create(255, 255, 0), STEPS, FRAME_DURATION_MS);

	// Breathe red
	GenerateBreathe(factory.Create(255, 0, 0), STEPS, FRAME_DURATION_MS);

	// Breathe purple
	GenerateBreathe(factory.Create(255, 0, 255), STEPS, FRAME_DURATION_MS);

	// Breathe green
	GenerateBreathe(factory.Create(0, 255, 0), STEPS, FRAME_DURATION_MS);

	// Breathe white
	GenerateBreathe(factory.Create(255, 255, 255), STEPS, FRAME_DURATION_MS);

	// Breathe blue
	GenerateBreathe(factory.Create(0, 0, 255), STEPS, FRAME_DURATION_MS);

	// Breathe brown
	GenerateBreathe(factory.Create(255, 120, 120), STEPS, FRAME_DURATION_MS);
}

std::wstring FreshBreatheAnimation::GetName() const
{
	return L"Fresh Breathe";
}

std::optional<Frame> FreshBreatheAnimation::GetFrame(uint32_t idx)
{
	return m_frames.GetFrame(idx);
}

bool FreshBreatheAnimation::IsSupportedKB(KeyboardType kbType) const
{
	return (kbType != KeyboardType::PER_KEY && kbType != KeyboardType::NONE);
}

uint32_t FreshBreatheAnimation::Size() const
{
	return m_frames.Size();
}

void FreshBreatheAnimation::AddFrame(const Frame& frame)
{
	m_frames.AddFrame(frame);
}

void FreshBreatheAnimation::GenerateBreathe(const Colour& targetColour, uint32_t steps, uint32_t stepTimeMs)
{
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
}