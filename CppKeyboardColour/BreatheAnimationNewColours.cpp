#include "stdafx.h"
#include "MathConstants.h"
#include "BreatheAnimationNewColours.h"

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

BreatheAnimationNewColours::BreatheAnimationNewColours() 
{
	// Breathe yellow
	GenerateBreathe(CreateColour(255, 255, 0), STEPS, FRAME_DURATION_MS);

	// Breathe red
	GenerateBreathe(CreateColour(255, 0, 0), STEPS, FRAME_DURATION_MS);

	// Breathe purple
	GenerateBreathe(CreateColour(255, 0, 255), STEPS, FRAME_DURATION_MS);

	// Breathe green
	GenerateBreathe(CreateColour(0, 255, 0), STEPS, FRAME_DURATION_MS);

	// Breathe white
	GenerateBreathe(CreateColour(255, 255, 255), STEPS, FRAME_DURATION_MS);

	// Breathe brown
	GenerateBreathe(CreateColour(255, 120, 120), STEPS, FRAME_DURATION_MS);
}

std::optional<Frame> BreatheAnimationNewColours::GetFrame(uint32_t idx) 
{
	return m_frames.GetFrame(idx);
}

bool BreatheAnimationNewColours::IsSupportedKB(KeyboardType kbType) const 
{
	return (kbType != KeyboardType::PER_KEY && kbType != KeyboardType::NONE);
}

uint32_t BreatheAnimationNewColours::Size() const 
{
	return m_frames.Size();
}

void BreatheAnimationNewColours::AddFrame(const Frame& frame)
{
	m_frames.AddFrame(frame);
}

Colour BreatheAnimationNewColours::CreateColour(uint8_t red, uint8_t green, uint8_t blue) 
{
	Colour colour{};

	colour[INDEX_COLOUR_RED] = red;
	colour[INDEX_COLOUR_GREEN] = green;
	colour[INDEX_COLOUR_BLUE] = blue;

	return colour;
}

void BreatheAnimationNewColours::GenerateBreathe(const Colour& targetColour, uint32_t steps, uint32_t stepTimeMs)
{
	for (size_t i = 0; i < steps; ++i) 
	{
		Colour currentColour{};

		for (size_t channel = 0; channel < targetColour.size(); ++channel) 
		{
			const auto channelPercent = (180.0f / steps) * i;
			currentColour[channel] = targetColour[channel] * std::sin(channelPercent * (MATH_PI / 180.0f));
		}

		Frame frame(Zone::ALL, currentColour, stepTimeMs);

		this->AddFrame(frame);
	}
}