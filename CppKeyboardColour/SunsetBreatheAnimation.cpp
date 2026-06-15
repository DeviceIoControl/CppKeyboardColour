// Created by DeviceIoControl

#include "stdafx.h"
#include "SunsetBreatheAnimation.h"
#include "ColourFactory.h"

constexpr size_t FRAMES = 50;
constexpr size_t FRAME_DURATION_MS = 40;

SunsetBreatheAnimation::SunsetBreatheAnimation()
{
	ColourFactory const factory{};

	auto const sunsetPink = factory.Create(255, 95, 149);
	
	auto const sunsetBreathe = m_patternGenerator.GenerateBreathe(sunsetPink, FRAMES, FRAME_DURATION_MS);
	m_frames.AddFrames(sunsetBreathe);
}

std::wstring SunsetBreatheAnimation::GetName() const
{
	return L"Sunset Breathe";
}

std::optional<Frame> SunsetBreatheAnimation::GetFrame(uint32_t idx)
{
	return m_frames.GetFrame(0);
}

bool SunsetBreatheAnimation::IsSupportedKB(KeyboardType kbType) const
{
	return kbType != KeyboardType::PER_KEY && kbType != KeyboardType::NONE;
}

uint32_t SunsetBreatheAnimation::Size() const
{
	return m_frames.Size();
}