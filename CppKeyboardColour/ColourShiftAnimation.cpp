// Created by DeviceIoControl

#include "stdafx.h"
#include "KeyboardType.h"
#include "ColourShiftAnimation.h"

ColourShiftAnimation::ColourShiftAnimation()
{
	const Colours rgbColours {
		m_factory.Create(ColourValue::RED),
		m_factory.Create(ColourValue::GREEN),
		m_factory.Create(ColourValue::BLUE),
	};

	const Colours brgColours {
		m_factory.Create(ColourValue::BLUE),
		m_factory.Create(ColourValue::RED),
		m_factory.Create(ColourValue::GREEN),
	};

	const Colours gbrColours {
		m_factory.Create(ColourValue::GREEN),
		m_factory.Create(ColourValue::BLUE),
		m_factory.Create(ColourValue::RED),
	};

	const auto rgbToBrg = m_frameGenerator.GenerateColourBlendRotation(DeviceMask::Keyboard, rgbColours, brgColours, 255, 0);
	const auto brgToGbr = m_frameGenerator.GenerateColourBlendRotation(DeviceMask::Keyboard, brgColours, gbrColours, 255, 0);
	const auto gbrToRgb = m_frameGenerator.GenerateColourBlendRotation(DeviceMask::Keyboard, gbrColours, rgbColours, 255, 0);

	// Transitions with interleaved delay frames.
	m_frames.AddFrames(rgbToBrg);
	m_frames.AddFrame(DeviceMask::Keyboard, Zone::LEFT, brgColours[ZoneToArrayIndex(Zone::LEFT)], 5000);
	m_frames.AddFrames(brgToGbr);
	m_frames.AddFrame(DeviceMask::Keyboard, Zone::LEFT, gbrColours[ZoneToArrayIndex(Zone::LEFT)], 5000);
	m_frames.AddFrames(gbrToRgb);
	m_frames.AddFrame(DeviceMask::Keyboard, Zone::LEFT, rgbColours[ZoneToArrayIndex(Zone::LEFT)], 5000);
}

std::wstring ColourShiftAnimation::GetName() const
{
	return L"Colour Shift";
}

std::optional<Frame> ColourShiftAnimation::GetFrame(uint32_t idx) 
{
	return m_frames.GetFrame(idx);
}

bool ColourShiftAnimation::IsHostSupported(const IHost* pHost) const
{
	return (pHost) ? pHost->GetKeyboardType() == KeyboardType::TRIPLE_ZONE : false;
}

uint32_t ColourShiftAnimation::Size() const 
{
	return m_frames.Size();
}
