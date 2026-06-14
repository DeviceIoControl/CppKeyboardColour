// Created by DeviceIoControl

#include "stdafx.h"
#include "SakuraTransformAnimation.h"
#include "ColourFactory.h"

#define STEPS 150
#define STEP_DURATION_MS 20

//
// Sakura Pink: RGB(255,30,197)
// Rose Pink: RGB(255, 30, 185)
// Soft Lavender: RGB(210, 30, 255)
//

SakuraTransformAnimation::SakuraTransformAnimation() 
{
	ColourFactory factory{};

	auto const sakuraPink = factory.Create(255, 80, 197);
	auto const rosePink = factory.Create(255, 80, 185);
	auto const softLavender = factory.Create(180, 80, 255);

	// Transition Sakura Pink to Rose Pink
	auto const sakuraToRose = m_patternGenerator.GenerateColourTransform(sakuraPink, rosePink, STEPS, STEP_DURATION_MS);
	m_frames.AddFrames(sakuraToRose);

	// Wait 2 seconds
	Frame const roseFrame(Zone::ALL, rosePink, 2000);
	m_frames.AddFrame(roseFrame);

	// Transition from Rose Pink to Soft Lavendar
	auto const roseToLavender = m_patternGenerator.GenerateColourTransform(rosePink, softLavender, STEPS, STEP_DURATION_MS);
	m_frames.AddFrames(roseToLavender);

	// Wait 2 seconds
	Frame const lavendarFrame(Zone::ALL, softLavender, 2000);
	m_frames.AddFrame(lavendarFrame);

	// Cycle back to Sakura Pink
	auto const lavenderToSakura = m_patternGenerator.GenerateColourTransform(softLavender, sakuraPink, STEPS, STEP_DURATION_MS);
	m_frames.AddFrames(lavenderToSakura);

	// Wait 2 seconds
	Frame const sakuraFrame(Zone::ALL, sakuraPink, 2000);
	m_frames.AddFrame(sakuraFrame);
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

void SakuraTransformAnimation::AddFrame(const Frame& frame) 
{
	m_frames.AddFrame(frame);
}