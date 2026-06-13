#include "stdafx.h"
#include "PinkBreatheAnimation.h"
#include "ColourFactory.h"

PinkBreatheAnimation::PinkBreatheAnimation() 
{
	ColourFactory factory{};

	auto const pink = factory.Create(255, 160, 190);
	auto const ascendPattern = m_patternGenerator.GenerateAscendingPattern(pink, 100, 20);

	Frame const pinkFrame(Zone::ALL, pink, 4000);

	auto const descendPattern = m_patternGenerator.GenerateDescendingPattern(pink, 100, 20);

	m_frames.AddFrames(ascendPattern);
	m_frames.AddFrame(pinkFrame);
	m_frames.AddFrames(descendPattern);
}

std::wstring PinkBreatheAnimation::GetName() const 
{
	return L"Pink Breathe";
}

std::optional<Frame> PinkBreatheAnimation::GetFrame(uint32_t idx) 
{
	return m_frames.GetFrame(idx);
}

bool PinkBreatheAnimation::IsSupportedKB(KeyboardType kbType) const 
{
	return kbType != KeyboardType::PER_KEY && kbType != KeyboardType::NONE;
}

uint32_t PinkBreatheAnimation::Size() const 
{
	return m_frames.Size();
}

void PinkBreatheAnimation::AddFrame(const Frame& frame) 
{
	m_frames.AddFrame(frame);
}