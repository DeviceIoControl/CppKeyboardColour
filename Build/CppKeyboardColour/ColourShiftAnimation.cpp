// Created by DeviceIoControl

#include "stdafx.h"
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

void ColourShiftAnimation::AddFrame(const Frame& frame) 
{
	m_frames.AddFrame(frame);
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
		for (int y = 0; y < 3; ++y)
		{
			Colour zoneColour{};

			zoneColour[INDEX_COLOUR_RED] = rgb[y][INDEX_COLOUR_RED];
			zoneColour[INDEX_COLOUR_GREEN] = rgb[y][INDEX_COLOUR_GREEN];
			zoneColour[INDEX_COLOUR_BLUE] = rgb[y][INDEX_COLOUR_BLUE];

			m_frames.AddFrame((Zone)y, zoneColour, 0);

			rgb[y][y]--;
			rgb[y][(y + 2) % 3]++;
		}
	}
}

void ColourShiftAnimation::GeneratePhase2(uint8_t(&rgb)[3][3])
{
	for (int i = 0; i < 0xFF; ++i)
	{
		for (int y = 0; y < 3; ++y)
		{
			Colour zoneColour{};
			zoneColour[INDEX_COLOUR_RED] = rgb[y][INDEX_COLOUR_RED];
			zoneColour[INDEX_COLOUR_GREEN] = rgb[y][INDEX_COLOUR_GREEN];
			zoneColour[INDEX_COLOUR_BLUE] = rgb[y][INDEX_COLOUR_BLUE];

			m_frames.AddFrame((Zone)y, zoneColour, 0);

			rgb[y][(y + 2) % 3]--;
			rgb[y][(y + 1) % 3]++;
		}
	}
}

void  ColourShiftAnimation::GeneratePhase3(uint8_t(&rgb)[3][3])
{
	for (int i = 0; i < 0xFF; ++i)
	{
		for (int y = 0; y < 3; ++y)
		{
			Colour zoneColour{};

			zoneColour[INDEX_COLOUR_RED] = rgb[y][INDEX_COLOUR_RED];
			zoneColour[INDEX_COLOUR_GREEN] = rgb[y][INDEX_COLOUR_GREEN];
			zoneColour[INDEX_COLOUR_BLUE] = rgb[y][INDEX_COLOUR_BLUE];

			m_frames.AddFrame((Zone)y, zoneColour, 0);

			rgb[y][(y + 1) % 3]--;
			rgb[y][y]++;
		}
	}
}

void ColourShiftAnimation::GenerateDelayFrame(const Frame& frame)
{
	Frame intermediateFrame(frame);
	intermediateFrame.ms_time = 5000;

	m_frames.AddFrame(intermediateFrame);
}
