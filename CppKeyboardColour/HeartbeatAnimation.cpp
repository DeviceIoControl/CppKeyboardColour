// Created by DeviceIoControl

#include "stdafx.h"
#include "HeartbeatAnimation.h"
#include "ColourFactory.h"

HeartbeatAnimation::HeartbeatAnimation()
{
	ColourFactory const factory{};

	const auto pulseColour = factory.Create(255, 0, 0);

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

bool HeartbeatAnimation::IsHostSupported(const IHost* pHost) const
{
	return (pHost) ? pHost->GetKeyboardType() != KeyboardType::PER_KEY && pHost->GetKeyboardType() != KeyboardType::NONE : false;
}

uint32_t HeartbeatAnimation::Size() const
{
	return m_frames.Size();
}

void HeartbeatAnimation::GeneratePulse(const Colour& targetColour, uint32_t beatTimeMs)
{
	const auto pulsePattern = m_patternGenerator.GeneratePulse(DeviceMask::Keyboard, targetColour, beatTimeMs);
	m_frames.AddFrames(pulsePattern);
}