/*#include "stdafx.h"
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
}*/
#include "stdafx.h"
#include "MathConstants.h"
#include "BreatheAnimationNewColours.h"
#include "ColourFactory.h"

//
// rgb(255, 255, 0)   : Yellow 🟡
// rgb(255, 0, 0)     : Red 🔴
// rgb(255, 0, 255)   : Magenta 🌸
// rgb(0, 255, 0)     : Lime Green 🟢
// rgb(255, 255, 255) : White ⚪
// rgb(0, 0, 255)     : Blue 🔵
// rgb(255, 120, 120) : Pastel Red 🍑
// rgb(255, 165, 0)   : Orange 🟠
// rgb(128, 0, 128)   : Purple 🍇
// rgb(0, 255, 255)   : Cyan 🧊
// rgb(255, 20, 147)  : Deep Pink 🎀
// rgb(139, 69, 19)   : Saddle Brown 🟫
// rgb(255, 192, 203) : Pink 💖
// rgb(173, 216, 230) : Light Blue 💧
// rgb(144, 238, 144) : Light Green 🍃
// rgb(240, 230, 140) : Khaki 🌾
// rgb(75, 0, 130)    : Indigo 🌌
// rgb(0, 100, 0)     : Dark Green 🌲
// rgb(139, 0, 0)     : Dark Red 🍷
// rgb(100, 149, 237) : Cornflower Blue 🥣
// rgb(192, 192, 192) : Silver 🩶
// rgb(128, 128, 128) : Gray 🗿
//

constexpr size_t STEPS = 40.0f;
constexpr size_t FRAME_DURATION_MS = 45;

FreshBreatheAnimation::FreshBreatheAnimation()
{
	ColourFactory factory{};

	GenerateBreathe(factory.Create(255, 255, 0), STEPS, FRAME_DURATION_MS);   // Yellow
	GenerateBreathe(factory.Create(255, 0, 0), STEPS, FRAME_DURATION_MS);     // Red
	GenerateBreathe(factory.Create(255, 0, 255), STEPS, FRAME_DURATION_MS);   // Magenta
	GenerateBreathe(factory.Create(0, 255, 0), STEPS, FRAME_DURATION_MS);     // Lime Green
	GenerateBreathe(factory.Create(255, 255, 255), STEPS, FRAME_DURATION_MS); // White
	GenerateBreathe(factory.Create(0, 0, 255), STEPS, FRAME_DURATION_MS);     // Blue
	GenerateBreathe(factory.Create(255, 120, 120), STEPS, FRAME_DURATION_MS); // Pastel Red

	// --- New colors added below ---

	// Vibrant colors
	GenerateBreathe(factory.Create(255, 165, 0), STEPS, FRAME_DURATION_MS);  // Orange 🟠
	GenerateBreathe(factory.Create(128, 0, 128), STEPS, FRAME_DURATION_MS);  // Purple 🍇
	GenerateBreathe(factory.Create(0, 255, 255), STEPS, FRAME_DURATION_MS);  // Cyan 🧊
	GenerateBreathe(factory.Create(255, 20, 147), STEPS, FRAME_DURATION_MS); // Deep Pink 🎀
	GenerateBreathe(factory.Create(139, 69, 19), STEPS, FRAME_DURATION_MS);  // Saddle Brown 🟫

	// Pastel colors
	GenerateBreathe(factory.Create(255, 192, 203), STEPS, FRAME_DURATION_MS); // Pink 💖
	GenerateBreathe(factory.Create(173, 216, 230), STEPS, FRAME_DURATION_MS); // Light Blue 💧
	GenerateBreathe(factory.Create(144, 238, 144), STEPS, FRAME_DURATION_MS); // Light Green 🍃
	GenerateBreathe(factory.Create(240, 230, 140), STEPS, FRAME_DURATION_MS); // Khaki 🌾

	// Darker shades
	GenerateBreathe(factory.Create(75, 0, 130), STEPS, FRAME_DURATION_MS);   // Indigo 🌌
	GenerateBreathe(factory.Create(0, 100, 0), STEPS, FRAME_DURATION_MS);    // Dark Green 🌲
	GenerateBreathe(factory.Create(139, 0, 0), STEPS, FRAME_DURATION_MS);    // Dark Red 🍷
	GenerateBreathe(factory.Create(100, 149, 237), STEPS, FRAME_DURATION_MS); // Cornflower Blue 🥣

	// Monochrome shades
	GenerateBreathe(factory.Create(192, 192, 192), STEPS, FRAME_DURATION_MS); // Silver 🩶
	GenerateBreathe(factory.Create(128, 128, 128), STEPS, FRAME_DURATION_MS); // Gray 🗿
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