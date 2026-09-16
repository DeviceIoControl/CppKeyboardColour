// Created by DeviceIoControl

#include "stdafx.h"
#include "BreatheAnimation.h"
#include "ColourFactory.h"

constexpr size_t STEPS = 40;
constexpr size_t FRAME_DURATION_MS = 25;

BreatheAnimation::BreatheAnimation()
{
	ColourFactory factory{};

	const auto red = factory.Create(ColourValue::RED);
	const auto green = factory.Create(ColourValue::GREEN);
	const auto blue = factory.Create(ColourValue::BLUE);

	const auto redBreathePattern = m_patternGenerator.GenerateBreathe(DeviceMask::Keyboard, red, STEPS, FRAME_DURATION_MS);
	const auto greenBreathePattern = m_patternGenerator.GenerateBreathe(DeviceMask::Keyboard, green, STEPS, FRAME_DURATION_MS);
	const auto blueBreathePattern = m_patternGenerator.GenerateBreathe(DeviceMask::Keyboard, blue, STEPS, FRAME_DURATION_MS);

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

bool BreatheAnimation::IsHostSupported(const IHost* pHost) const
{
	return (pHost) ? pHost->GetKeyboardType() != KeyboardType::PER_KEY && pHost->GetKeyboardType() != KeyboardType::NONE : false;
}

uint32_t BreatheAnimation::Size() const
{
	return m_frames.Size();
}