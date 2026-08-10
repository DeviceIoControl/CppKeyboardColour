// Created by DeviceIoControl

#include "stdafx.h"
#include "SunsetBreatheAnimation.h"
#include "ColourFactory.h"

constexpr size_t FRAMES = 50;
constexpr size_t FRAME_DURATION_MS = 40;

SunsetBreatheAnimation::SunsetBreatheAnimation()
{
	ColourFactory factory{};

	auto const sunsetPink = factory.Create(255, 95, 149);

	auto const ascendPattern = m_patternGenerator.GenerateAscendingPattern(DeviceMask::Keyboard, sunsetPink, FRAMES, FRAME_DURATION_MS);
	auto const descendPattern = m_patternGenerator.GenerateDescendingPattern(DeviceMask::Keyboard, sunsetPink, FRAMES, FRAME_DURATION_MS);

	m_frames.AddFrames(ascendPattern);
	m_frames.AddFrame(DeviceMask::Keyboard, Zone::ALL, sunsetPink, 4000);
	m_frames.AddFrames(descendPattern);
}

std::wstring SunsetBreatheAnimation::GetName() const
{
	return L"Sunset Breathe";
}

std::optional<Frame> SunsetBreatheAnimation::GetFrame(uint32_t idx)
{
	return m_frames.GetFrame(idx);
}

bool SunsetBreatheAnimation::IsHostSupported(const IHost* pHost) const
{
	return pHost->GetKeyboardType() != KeyboardType::PER_KEY && pHost->GetKeyboardType() != KeyboardType::NONE;
}

uint32_t SunsetBreatheAnimation::Size() const
{
	return m_frames.Size();
}