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

	auto const sakuraPink = factory.Create(255, 110, 168);
	auto const sunsetPink = factory.Create(255, 95, 149);

	auto const sakuraToSunset = m_patternGenerator.GenerateColourTransform(sakuraPink, sunsetPink, FRAMES, FRAME_DURATION_MS);
	m_frames.AddFrames(sakuraToSunset);

	m_frames.AddFrame(Zone::ALL, sunsetPink, COLOUR_DURATION_MS);

	auto const sunsetToSakura = m_patternGenerator.GenerateColourTransform( sunsetPink, sakuraPink, FRAMES, FRAME_DURATION_MS);
	m_frames.AddFrames(sakuraToSunset);

	m_frames.AddFrame(Zone::ALL, sakuraPink, COLOUR_DURATION_MS);
}

std::wstring SakuraSunsetAnimation::GetName() const 
{
	return L"Sakura Sunset";
}

std::optional<Frame> SakuraSunsetAnimation::GetFrame(uint32_t idx)
{
	return m_frames.GetFrame(idx);
}

bool SakuraSunsetAnimation::IsSupportedKB(KeyboardType kbType) const
{
	return kbType != KeyboardType::PER_KEY && kbType != KeyboardType::NONE;
}

uint32_t SakuraSunsetAnimation::Size() const
{
	return m_frames.Size();
}