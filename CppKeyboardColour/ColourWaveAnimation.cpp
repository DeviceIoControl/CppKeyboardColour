// Created by DeviceIoControl

#include "stdafx.h"
#include "ColourWaveAnimation.h"

constexpr size_t STEPS = 50;
constexpr size_t FRAME_DURATION_MS = 25;

ColourWaveAnimation::ColourWaveAnimation()
{
	const auto red = m_factory.Create(ColourValue::RED);
	const auto green = m_factory.Create(ColourValue::GREEN);
	const auto blue = m_factory.Create(ColourValue::BLUE);

	const auto redWaveFrames = m_frameGenerator.GenerateColourWavePattern(DeviceMask::Keyboard, red, STEPS, FRAME_DURATION_MS);
	const auto greenWaveFrames = m_frameGenerator.GenerateColourWavePattern(DeviceMask::Keyboard, green, STEPS, FRAME_DURATION_MS);
	const auto blueWaveFrames = m_frameGenerator.GenerateColourWavePattern(DeviceMask::Keyboard, blue, STEPS, FRAME_DURATION_MS);

	m_frames.AddFrames(redWaveFrames);
	m_frames.AddFrames(greenWaveFrames);
	m_frames.AddFrames(blueWaveFrames);
}

std::wstring ColourWaveAnimation::GetName() const 
{
	return L"Colour Wave";
}

std::optional<Frame> ColourWaveAnimation::GetFrame(uint32_t idx)
{
	return m_frames.GetFrame(idx);
}

bool ColourWaveAnimation::IsHostSupported(const IHost* pHost) const
{
	return (pHost) ? pHost->GetKeyboardType() == KeyboardType::TRIPLE_ZONE : false;
}

uint32_t ColourWaveAnimation::Size() const
{
	return m_frames.Size();
}