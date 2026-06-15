// Created by DeviceIoControl

#include "stdafx.h"
#include "SakuraTransformAnimation.h"
#include "ColourFactory.h"

constexpr size_t FRAMES = 40;
constexpr size_t FRAME_DURATION_MS = 50;
constexpr size_t COLOUR_DURATION_MS = 3000;

//
// 0xff6ea8 (255, 110, 168) - Sakura Pink
// 0xff5f95 (255, 95, 149) - Sunset Pink
// 0xdc46dc (220, 70, 220) - Pink Violet
// 0xff6ea8 (255, 110, 168) - Sakura Pink
//
// 0xff6ea8 -> 0xff5f95 -> 0xdc46dc -> 0xff6ea8
//

SakuraTransformAnimation::SakuraTransformAnimation()
{
	ColourFactory const factory{};

	auto const sakuraPink = factory.Create(255, 110, 168);
	auto const sunsetPink = factory.Create(255, 95, 149);
	auto const pinkViolet = factory.Create(220, 70, 220);

	auto const sakuraToSunset = m_patternGenerator.GenerateColourTransform(sakuraPink, sunsetPink, FRAMES, FRAME_DURATION_MS);
	m_frames.AddFrames(sakuraToSunset);

	m_frames.AddFrame(Zone::ALL, sunsetPink, COLOUR_DURATION_MS);

	auto const sunsetToViolet = m_patternGenerator.GenerateColourTransform(sunsetPink, pinkViolet, FRAMES, FRAME_DURATION_MS);
	m_frames.AddFrames(sunsetToViolet);

	m_frames.AddFrame(Zone::ALL, pinkViolet, COLOUR_DURATION_MS);

	auto const violetToSakura = m_patternGenerator.GenerateColourTransform(pinkViolet, sakuraPink, FRAMES, FRAME_DURATION_MS);
	m_frames.AddFrames(violetToSakura);

	m_frames.AddFrame(Zone::ALL, sakuraPink, COLOUR_DURATION_MS);
}

std::wstring SakuraTransformAnimation::GetName() const
{
	return L"Sakura Transform";
}

std::optional<Frame> SakuraTransformAnimation::GetFrame(uint32_t idx)
{
	return m_frames.GetFrame(idx);
}

bool SakuraTransformAnimation::IsSupportedKB(KeyboardType kbType) const
{
	return kbType != KeyboardType::PER_KEY && kbType != KeyboardType::NONE;
}

uint32_t SakuraTransformAnimation::Size() const
{
	return m_frames.Size();
}