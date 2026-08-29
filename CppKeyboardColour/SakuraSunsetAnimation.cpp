// Created by DeviceIoControl

#include "stdafx.h"
#include "SakuraSunsetAnimation.h"
#include "ColourFactory.h"

constexpr size_t FRAMES = 40;
constexpr size_t FRAME_DURATION_MS = 50;
constexpr size_t COLOUR_DURATION_MS = 3000;

SakuraSunsetAnimation::SakuraSunsetAnimation() 
{
	ColourFactory const factory{};

	const auto sakuraPink = factory.Create(255, 110, 168);
	const auto sunsetPink = factory.Create(255, 95, 149);

	const auto sakuraToSunset = m_patternGenerator.GenerateColourBlend(DeviceMask::Keyboard, sakuraPink, sunsetPink, FRAMES, FRAME_DURATION_MS);
	m_frames.AddFrames(sakuraToSunset);

	m_frames.AddFrame(DeviceMask::Keyboard, Zone::ALL, sunsetPink, COLOUR_DURATION_MS);

	const auto sunsetToSakura = m_patternGenerator.GenerateColourBlend(DeviceMask::Keyboard, sunsetPink, sakuraPink, FRAMES, FRAME_DURATION_MS);
	m_frames.AddFrames(sakuraToSunset);

	m_frames.AddFrame(DeviceMask::Keyboard, Zone::ALL, sakuraPink, COLOUR_DURATION_MS);
}

std::wstring SakuraSunsetAnimation::GetName() const 
{
	return L"Sakura Sunset";
}

std::optional<Frame> SakuraSunsetAnimation::GetFrame(uint32_t idx)
{
	return m_frames.GetFrame(idx);
}

bool SakuraSunsetAnimation::IsHostSupported(const IHost* pHost) const
{
	return (pHost) ? pHost->GetKeyboardType() != KeyboardType::PER_KEY && pHost->GetKeyboardType() != KeyboardType::NONE : false;
}

uint32_t SakuraSunsetAnimation::Size() const
{
	return m_frames.Size();
}