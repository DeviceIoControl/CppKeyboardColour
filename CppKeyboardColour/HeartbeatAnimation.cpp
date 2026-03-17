// Created by DeviceIoControl

#include "stdafx.h"
#include "HeartbeatAnimation.h"
#include "ColourFactory.h"

HeartbeatAnimation::HeartbeatAnimation()
{
	ColourFactory factory{};

	auto const pulseColour = factory.Create(255, 0, 0);

	this->GeneratePulse(pulseColour, 60);
}

std::wstring HeartbeatAnimation::GetName() const
{
	return L"Heartbeat";
}

std::optional<Frame> HeartbeatAnimation::GetFrame(uint32_t idx)
{
	return m_frames.GetFrame(idx);
}

bool HeartbeatAnimation::IsSupportedKB(KeyboardType kbType) const
{
	return kbType == KeyboardType::SINGLE_ZONE || kbType == KeyboardType::TRIPLE_ZONE;
}

uint32_t HeartbeatAnimation::Size() const
{
	return m_frames.Size();
}

void HeartbeatAnimation::AddFrame(const Frame& frame)
{
	m_frames.AddFrame(frame);
}

void HeartbeatAnimation::GeneratePulse(const Colour& targetColour, uint32_t beatTimeMs)
{
	Colour blankColour{};

	ColourFactory factory{};

	auto const firstPulseColour = factory.Create(
		static_cast<uint8_t>(targetColour[INDEX_COLOUR_RED] * 0.33f),
		static_cast<uint8_t>(targetColour[INDEX_COLOUR_GREEN] * 0.33f),
		static_cast<uint8_t>(targetColour[INDEX_COLOUR_BLUE] * 0.33f)
	);

	Frame blankFame(Zone::ALL, blankColour, 1250);
	Frame interBlankFame(Zone::ALL, blankColour, beatTimeMs / 2);
	Frame firstPulse(Zone::ALL, firstPulseColour, beatTimeMs);
	Frame secondPulse(Zone::ALL, targetColour, beatTimeMs);

	this->AddFrame(blankFame);
	this->AddFrame(firstPulse);
	this->AddFrame(interBlankFame);
	this->AddFrame(secondPulse);
	this->AddFrame(interBlankFame);
}