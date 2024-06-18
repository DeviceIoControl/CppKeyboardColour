// Created by DeviceIoControl

#include "stdafx.h"
#include "BreatheAnimation.h"

constexpr size_t STEPS = 50.0f;
constexpr float MATH_PI = 3.14159f;

BreatheAnimation::BreatheAnimation()
{
	this->GeneratePhase1();
	this->GeneratePhase2();
	this->GeneratePhase3();
}

void BreatheAnimation::AddFrame(const Frame& frame)
{
	m_frames.AddFrame(frame);
}

std::optional<Frame> BreatheAnimation::GetFrame(uint32_t idx) 
{
	return m_frames.GetFrame(idx);
}

bool BreatheAnimation::IsSupportedKB(KeyboardType kbType) const 
{
	return kbType != KeyboardType::NONE;
}

uint32_t BreatheAnimation::Size() const 
{
	return m_frames.Size();
}

void BreatheAnimation::GeneratePhase1()
{
	for (size_t i = 0; i < STEPS; ++i)
	{
		Colour colour{};
		
		// FIXME: atan2 can result in values above 1.0f which causes theme inconsistencies.
		colour[INDEX_COLOUR_RED] = 255 * std::atan2((180.0f / STEPS) * i, 180.0f / MATH_PI);
		colour[INDEX_COLOUR_GREEN] = 0;
		colour[INDEX_COLOUR_BLUE] = 0;

		m_frames.AddFrame(Zone::ALL, colour, 175);
	}
}

void BreatheAnimation::GeneratePhase2()
{
	for (size_t i = 0; i < STEPS; ++i)
	{
		Colour colour{};

		colour[INDEX_COLOUR_RED] = 0;

		// FIXME: atan2 can result in values above 1.0f which causes theme inconsistencies.
		colour[INDEX_COLOUR_GREEN] = 255 * std::atan2((180.0f / STEPS) * i, 180.0f / MATH_PI);
		colour[INDEX_COLOUR_BLUE] = 0;

		m_frames.AddFrame(Zone::ALL, colour, 175);
	}
}

void BreatheAnimation::GeneratePhase3()
{
	for (size_t i = 0; i < STEPS; ++i)
	{
		Colour colour{};

		colour[INDEX_COLOUR_RED] = 0;
		colour[INDEX_COLOUR_GREEN] = 0;

		// FIXME: atan2 can result in values above 1.0f which causes theme inconsistencies.
		colour[INDEX_COLOUR_BLUE] = 255 * std::atan2((180.0f / STEPS) * i, 180.0f / MATH_PI);

		m_frames.AddFrame(Zone::ALL, colour, 175);
	}
}
