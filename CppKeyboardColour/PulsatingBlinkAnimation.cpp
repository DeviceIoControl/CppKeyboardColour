// Created by DeviceIoControl

#include "stdafx.h"
#include "PulsatingBlinkAnimation.h"
#include "ColourFactory.h"

// Sky Blue - rgb(135, 206, 235)
// Forest Green - rgb(34, 139, 34)
// Sunset Orange - rgb(255, 69, 0)
// Rose Pink - rgb(255, 102, 204)

#define BLINK_TIME_MS 200

PulsatingBlinkAnimation::PulsatingBlinkAnimation()
{
	ColourFactory const factory{};

	auto const skyBlue = factory.Create(135, 206, 235);
	auto const forestGreen = factory.Create(34, 139, 34);
	auto const sunsetOrange = factory.Create(255, 69, 0);
	auto const rosePink = factory.Create(255, 102, 204);

	this->GenerateBlink(skyBlue, BLINK_TIME_MS);
	this->GenerateBlink(forestGreen, BLINK_TIME_MS);
	this->GenerateBlink(sunsetOrange, BLINK_TIME_MS);
	this->GenerateBlink(rosePink, BLINK_TIME_MS);
}

std::wstring PulsatingBlinkAnimation::GetName() const 
{
	return L"Pulsating Blink";
}

std::optional<Frame> PulsatingBlinkAnimation::GetFrame(uint32_t idx)
{
	return m_frames.GetFrame(idx);
}

bool PulsatingBlinkAnimation::IsSupportedKB(KeyboardType kbType) const
{
	return kbType != KeyboardType::PER_KEY && kbType != KeyboardType::NONE;
}

uint32_t PulsatingBlinkAnimation::Size() const
{
	return m_frames.Size();
}

void PulsatingBlinkAnimation::GenerateBlink(const Colour& colour, uint32_t blinkTimeMs)
{
	auto const blinkPattern = m_patternGenerator.GenerateBlink(colour, blinkTimeMs);
	m_frames.AddFrames(blinkPattern);
}