// Created by DeviceIoControl

#include "stdafx.h"
#include "ColourShiftAnimation.h"

ColourShiftAnimation::ColourShiftAnimation()
{
	Colours colours {
		m_factory.Create(0xff, 0x00, 0x00),
		m_factory.Create(0x00, 0xff, 0x00),
		m_factory.Create(0x00, 0x00, 0xff),
	};

	this->GeneratePhase1(colours);
	auto frame1 = m_frames.GetFrame(m_frames.Size() - 1);
	this->GenerateDelayFrame(frame1.value());

	this->GeneratePhase2(colours);
	auto frame2 = m_frames.GetFrame(m_frames.Size() - 1);
	this->GenerateDelayFrame(frame2.value());
	
	this->GeneratePhase3(colours);
	auto frame3 = m_frames.GetFrame(m_frames.Size() - 1);
	this->GenerateDelayFrame(frame3.value());
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

void ColourShiftAnimation::GeneratePhase1(Colours& colours)
{	
	for (int i = 0; i < 0xFF; ++i)
	{
		for (const auto currentZone : { Zone::LEFT,  Zone::MID, Zone::RIGHT })
		{
			const auto zoneColour = m_factory.Create(
				colours[ZoneToIndex(currentZone)][INDEX_COLOUR_RED],
				colours[ZoneToIndex(currentZone)][INDEX_COLOUR_GREEN],
				colours[ZoneToIndex(currentZone)][INDEX_COLOUR_BLUE]
			);

			m_frames.AddFrame(DeviceMask::Keyboard, currentZone, zoneColour, 0);

			colours[ZoneToIndex(currentZone)][ZoneToIndex(currentZone)]--;
			colours[ZoneToIndex(currentZone)][(ZoneToIndex(currentZone) + 2) % 3]++;
		}
	}
}

void ColourShiftAnimation::GeneratePhase2(Colours& colours)
{
	for (int i = 0; i < 0xFF; ++i)
	{
		for (const auto currentZone : { Zone::LEFT, Zone::MID, Zone::RIGHT })
		{
			const auto zoneColour = m_factory.Create(
				colours[ZoneToIndex(currentZone)][INDEX_COLOUR_RED],
				colours[ZoneToIndex(currentZone)][INDEX_COLOUR_GREEN],
				colours[ZoneToIndex(currentZone)][INDEX_COLOUR_BLUE]
			);

			m_frames.AddFrame(DeviceMask::Keyboard, currentZone, zoneColour, 0);

			colours[ZoneToIndex(currentZone)][(ZoneToIndex(currentZone) + 2) % 3]--;
			colours[ZoneToIndex(currentZone)][(ZoneToIndex(currentZone) + 1) % 3]++;
		}
	}
}

void ColourShiftAnimation::GeneratePhase3(Colours& colours)
{
	for (int i = 0; i < 0xFF; ++i)
	{
		for (const auto currentZone : { Zone::LEFT, Zone::MID, Zone::RIGHT })
		{
			const auto zoneColour = m_factory.Create(
				colours[ZoneToIndex(currentZone)][INDEX_COLOUR_RED],
				colours[ZoneToIndex(currentZone)][INDEX_COLOUR_GREEN],
				colours[ZoneToIndex(currentZone)][INDEX_COLOUR_BLUE]
			);

			m_frames.AddFrame(DeviceMask::Keyboard, currentZone, zoneColour, 0);

			colours[ZoneToIndex(currentZone)][(ZoneToIndex(currentZone) + 1) % 3]--;
			colours[ZoneToIndex(currentZone)][ZoneToIndex(currentZone)]++;
		}
	}
}

uint32_t ColourShiftAnimation::ZoneToIndex(Zone zone)
{
	return xstd::to_underlying(zone) - xstd::to_underlying(Zone::LEFT);
}

void ColourShiftAnimation::GenerateDelayFrame(const Frame& frame)
{
	m_frames.AddFrame(DeviceMask::Keyboard, frame.zone, frame.colour, 5000);
}
