// Created by DeviceIoControl

#include "stdafx.h"
#include "HeartbeatAnimation.h"
#include "ColourFactory.h"

HeartbeatAnimation::HeartbeatAnimation()
{
	ColourFactory const factory{};

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

void HeartbeatAnimation::GeneratePulse(const Colour& targetColour, uint32_t beatTimeMs)
{
	auto const pulsePattern = m_patternGenerator.GeneratePulse(targetColour, beatTimeMs);
	m_frames.AddFrames(pulsePattern);
}