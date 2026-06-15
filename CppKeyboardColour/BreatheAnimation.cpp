// Created by DeviceIoControl

#include "stdafx.h"
#include "BreatheAnimation.h"
#include "ColourFactory.h"

constexpr size_t STEPS = 40.0f;
constexpr size_t FRAME_DURATION_MS = 25;

BreatheAnimation::BreatheAnimation()
{
	ColourFactory factory{};

	auto const red = factory.Create(255, 0, 0);
	auto const green = factory.Create(0, 255, 0);
	auto const blue = factory.Create(0, 0, 255);

	auto const redBreathePattern = m_patternGenerator.GenerateBreathe(red, STEPS, FRAME_DURATION_MS);
	auto const greenBreathePattern = m_patternGenerator.GenerateBreathe(green, STEPS, FRAME_DURATION_MS);
	auto const blueBreathePattern = m_patternGenerator.GenerateBreathe(blue, STEPS, FRAME_DURATION_MS);

	m_frames.AddFrames(redBreathePattern);
	m_frames.AddFrames(greenBreathePattern);
	m_frames.AddFrames(blueBreathePattern);
}

std::wstring BreatheAnimation::GetName() const
{
	return L"Breathe";
}

std::optional<Frame> BreatheAnimation::GetFrame(uint32_t idx) 
{
	return m_frames.GetFrame(idx);
}

bool BreatheAnimation::IsSupportedKB(KeyboardType kbType) const 
{
	return kbType != KeyboardType::NONE;
}

uint32_t BreatheAnimation::Size() const 
{
	return m_frames.Size();
}