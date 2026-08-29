// Created by DeviceIoControl

#include "stdafx.h"
#include "ColourFactory.h"
#include "ColourTransformAnimation.h"
#include "Colour.h"
 
constexpr size_t STEPS = 40;
constexpr size_t FRAME_DURATION_MS = 25;

ColourTransformAnimation::ColourTransformAnimation()
{
	ColourFactory factory{};

	const auto red = factory.Create(255, 0, 0);
	const auto green = factory.Create(0, 255, 0);
	const auto blue = factory.Create(0, 0, 255);

	const auto redToGreen = m_patternGenerator.GenerateColourBlend(DeviceMask::Keyboard, red, green, STEPS, FRAME_DURATION_MS);
	m_frames.AddFrames(redToGreen);

	const auto greenToBlue = m_patternGenerator.GenerateColourBlend(DeviceMask::Keyboard, green, blue, STEPS, FRAME_DURATION_MS);
	m_frames.AddFrames(greenToBlue);

	const auto blueToRed = m_patternGenerator.GenerateColourBlend(DeviceMask::Keyboard, blue, red, STEPS, FRAME_DURATION_MS);
	m_frames.AddFrames(blueToRed);
}

std::wstring ColourTransformAnimation::GetName() const 
{
	return L"Colour Transform";
}

std::optional<Frame> ColourTransformAnimation::GetFrame(uint32_t idx)
{
	return m_frames.GetFrame(idx);
}

bool ColourTransformAnimation::IsHostSupported(const IHost* pHost) const
{
	return (pHost) ? pHost->GetKeyboardType() != KeyboardType::PER_KEY && pHost->GetKeyboardType() != KeyboardType::NONE : false;
}

uint32_t ColourTransformAnimation::Size() const 
{
	return m_frames.Size();
}


