// Created by DeviceIoControl

#include "stdafx.h"
#include "PinkBreatheAnimation.h"
#include "ColourFactory.h"

constexpr size_t FRAMES = 50;
constexpr size_t FRAME_DURATION_MS = 40;

PinkBreatheAnimation::PinkBreatheAnimation() 
{
	ColourFactory factory{};

	auto const pink = factory.Create(255, 110, 168);

	auto const ascendPattern = m_patternGenerator.GenerateAscendingPattern(pink, FRAMES, FRAME_DURATION_MS);
	auto const descendPattern = m_patternGenerator.GenerateDescendingPattern(pink, FRAMES, FRAME_DURATION_MS);

	m_frames.AddFrames(ascendPattern);
	m_frames.AddFrame(Zone::ALL, pink, 4000);
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