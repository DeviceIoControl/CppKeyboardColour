// Created by DeviceIoControl

#include "stdafx.h"
#include "ColourFactory.h"
#include "ColourTransformAnimation.h"
 
constexpr size_t STEPS = 40;
constexpr size_t FRAME_DURATION_MS = 25;

ColourTransformAnimation::ColourTransformAnimation()
{
	ColourFactory factory{};

	const auto red = factory.Create(255, 0, 0);
	const auto green = factory.Create(0, 255, 0);
	const auto blue = factory.Create(0, 0, 255);

	auto const redToGreen = m_patternGenerator.GenerateColourTransform(red, green, STEPS, FRAME_DURATION_MS);
	m_frames.AddFrames(redToGreen);

	auto const greenToBlue = m_patternGenerator.GenerateColourTransform(green, blue, STEPS, FRAME_DURATION_MS);
	m_frames.AddFrames(greenToBlue);

	auto const blueToRed = m_patternGenerator.GenerateColourTransform(blue, red, STEPS, FRAME_DURATION_MS);
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

bool ColourTransformAnimation::IsSupportedKB(KeyboardType kbType) const 
{
	return kbType != KeyboardType::PER_KEY && kbType != KeyboardType::NONE;
}

uint32_t ColourTransformAnimation::Size() const 
{
	return m_frames.Size();
}


