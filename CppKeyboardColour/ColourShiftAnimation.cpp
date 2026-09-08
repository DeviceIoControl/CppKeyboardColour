// Created by DeviceIoControl

#include "stdafx.h"
#include "KeyboardType.h"
#include "ColourShiftAnimation.h"

ColourShiftAnimation::ColourShiftAnimation()
{
	Colours const rgbColours {
		m_factory.Create(0xff, 0x00, 0x00),
		m_factory.Create(0x00, 0xff, 0x00),
		m_factory.Create(0x00, 0x00, 0xff),
	};

	Colours const brgColours {
		m_factory.Create(0x00, 0x00, 0xff),
		m_factory.Create(0xff, 0x00, 0x00),
		m_factory.Create(0x00, 0xff, 0x00),
	};

	Colours const gbrColours {
		m_factory.Create(0x00, 0xff, 0x00),
		m_factory.Create(0x00, 0x00, 0xff),
		m_factory.Create(0xff, 0x00, 0x00),
	};

	auto const rgbToBrg = m_frameGenerator.GenerateColourRotation(DeviceMask::Keyboard, rgbColours, brgColours, 255, 0);
	auto const brgToGbr = m_frameGenerator.GenerateColourRotation(DeviceMask::Keyboard, brgColours, gbrColours, 255, 0);
	auto const gbrToRgb = m_frameGenerator.GenerateColourRotation(DeviceMask::Keyboard, gbrColours, rgbColours, 255, 0);

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
