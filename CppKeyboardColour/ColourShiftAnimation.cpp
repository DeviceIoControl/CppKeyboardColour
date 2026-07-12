// Created by DeviceIoControl

#include "stdafx.h"
#include "ColourFactory.h"
#include "ColourShiftAnimation.h"

ColourShiftAnimation::ColourShiftAnimation()
{
	uint8_t rgb[3][3] =
	{
		{ 0xFF, 0x00, 0x00 },
		{ 0x00, 0xFF, 0x00 },
		{ 0x00, 0x00, 0xFF }
	};

	this->GeneratePhase1(rgb);
	auto frame1 = m_frames.GetFrame(m_frames.Size() - 1);
	this->GenerateDelayFrame(frame1.value());

	this->GeneratePhase2(rgb);
	auto frame2 = m_frames.GetFrame(m_frames.Size() - 1);
	this->GenerateDelayFrame(frame2.value());
	
	this->GeneratePhase3(rgb);
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

bool ColourShiftAnimation::IsSupportedKB(KeyboardType kbType) const
{
	return kbType == KeyboardType::TRIPLE_ZONE;
}

uint32_t ColourShiftAnimation::Size() const 
{
	return m_frames.Size();
}

void ColourShiftAnimation::GeneratePhase1(uint8_t(&rgb)[3][3])
{	
	for (int i = 0; i < 0xFF; ++i)
	{
		for (auto const currentZone : { Zone::LEFT,  Zone::MID, Zone::RIGHT })
		{
			auto const zoneColour = m_factory.Create(
				rgb[ZoneToIndex(currentZone)][INDEX_COLOUR_RED],
				rgb[ZoneToIndex(currentZone)][INDEX_COLOUR_GREEN],
				rgb[ZoneToIndex(currentZone)][INDEX_COLOUR_BLUE]
			);

			m_frames.AddFrame(currentZone, zoneColour, 0);

			rgb[ZoneToIndex(currentZone)][ZoneToIndex(currentZone)]--;
			rgb[ZoneToIndex(currentZone)][(ZoneToIndex(currentZone) + 2) % 3]++;
		}
	}
}

void ColourShiftAnimation::GeneratePhase2(uint8_t(&rgb)[3][3])
{
	for (int i = 0; i < 0xFF; ++i)
	{
		for (auto const currentZone : { Zone::LEFT, Zone::MID, Zone::RIGHT })
		{
			auto const zoneColour = m_factory.Create(
				rgb[ZoneToIndex(currentZone)][INDEX_COLOUR_RED],
				rgb[ZoneToIndex(currentZone)][INDEX_COLOUR_GREEN],
				rgb[ZoneToIndex(currentZone)][INDEX_COLOUR_BLUE]
			);

			m_frames.AddFrame(currentZone, zoneColour, 0);

			rgb[ZoneToIndex(currentZone)][(ZoneToIndex(currentZone) + 2) % 3]--;
			rgb[ZoneToIndex(currentZone)][(ZoneToIndex(currentZone) + 1) % 3]++;
		}
	}
}

void ColourShiftAnimation::GeneratePhase3(uint8_t(&rgb)[3][3])
{
	for (int i = 0; i < 0xFF; ++i)
	{
		for (auto const currentZone : { Zone::LEFT, Zone::MID, Zone::RIGHT })
		{
			auto const zoneColour = m_factory.Create(
				rgb[ZoneToIndex(currentZone)][INDEX_COLOUR_RED],
				rgb[ZoneToIndex(currentZone)][INDEX_COLOUR_GREEN],
				rgb[ZoneToIndex(currentZone)][INDEX_COLOUR_BLUE]
			);

			m_frames.AddFrame(currentZone, zoneColour, 0);

			rgb[ZoneToIndex(currentZone)][(ZoneToIndex(currentZone) + 1) % 3]--;
			rgb[ZoneToIndex(currentZone)][ZoneToIndex(currentZone)]++;
		}
	}
}

uint32_t ColourShiftAnimation::ZoneToIndex(Zone zone)
{
	return xstd::to_underlying(zone) - xstd::to_underlying(Zone::LEFT);
}

void ColourShiftAnimation::GenerateDelayFrame(const Frame& frame)
{
	m_frames.AddFrame(frame.zone, frame.colour, 5000);
}
