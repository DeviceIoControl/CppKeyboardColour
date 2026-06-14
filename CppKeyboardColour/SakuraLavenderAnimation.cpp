// Created by DeviceIoControl

#include "stdafx.h"
#include "SakuraLavenderAnimation.h"
#include "ColourFactory.h"

//
// Sakura Pink: RGB(255,183,197)
// Soft Lavender: RGB(210, 180, 255)
//

SakuraLavenderAnimation::SakuraLavenderAnimation() 
{
	ColourFactory factory{};

	auto const sakuraPink = factory.Create(255, 80, 197);
	auto const lavender = factory.Create(210, 80, 255);

	auto const sakuraToLavender = m_patternGenerator.GenerateColourTransform(sakuraPink, lavender, 100, 30);
	m_frames.AddFrames(sakuraToLavender);

	Frame const lavenderFrame(Zone::ALL, lavender, 2000);
	m_frames.AddFrame(lavenderFrame);

	auto const lavenderToSakura = m_patternGenerator.GenerateColourTransform(lavender, sakuraPink, 100, 30);
	m_frames.AddFrames(lavenderToSakura);

	Frame const sakuraFrame(Zone::ALL, sakuraPink, 2000);
	m_frames.AddFrame(sakuraFrame);
}

std::wstring SakuraLavenderAnimation::GetName() const 
{
	return L"Sakura Lavender";
}

std::optional<Frame> SakuraLavenderAnimation::GetFrame(uint32_t idx) 
{
	return m_frames.GetFrame(0);
}

bool SakuraLavenderAnimation::IsSupportedKB(KeyboardType kbType) const
{
	return kbType != KeyboardType::PER_KEY && kbType != KeyboardType::NONE;
}

uint32_t SakuraLavenderAnimation::Size() const 
{
	return m_frames.Size();
}

void SakuraLavenderAnimation::AddFrame(const Frame& frame)
{
	m_frames.AddFrame(frame);
}