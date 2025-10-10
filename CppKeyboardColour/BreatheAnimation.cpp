// Created by DeviceIoControl

#include "stdafx.h"
#include "MathConstants.h"
#include "BreatheAnimation.h"

constexpr size_t STEPS = 40.0f;
constexpr size_t FRAME_DURATION_MS = 45;

BreatheAnimation::BreatheAnimation()
{
	this->GeneratePhase1();
	this->GeneratePhase2();
	this->GeneratePhase3();
}

std::wstring BreatheAnimation::GetName() const
{
	return L"Breathe";
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
		
		const auto val = (180.0f / STEPS) * i;

		// Generate a sine wave for a breathing effect.
		colour[INDEX_COLOUR_RED] = 255 * std::sin(val * (MATH_PI / 180.0f));
		colour[INDEX_COLOUR_GREEN] = 0;
		colour[INDEX_COLOUR_GRAY] = 0;
		colour[INDEX_COLOUR_BLUE] = 0;

		m_frames.AddFrame(Zone::ALL, colour, FRAME_DURATION_MS);
	}
}

void BreatheAnimation::GeneratePhase2()
{
	for (size_t i = 0; i < STEPS; ++i)
	{
		Colour colour{};
		const auto val = (180.0f / STEPS) * i;

		// Generate a sine wave for a breathing effect.
		colour[INDEX_COLOUR_GREEN] = 255 * std::sin(val * (MATH_PI / 180.0f));
		colour[INDEX_COLOUR_RED] = 0;
		colour[INDEX_COLOUR_BLUE] = 0;
		colour[INDEX_COLOUR_GRAY] = 0;

		m_frames.AddFrame(Zone::ALL, colour, FRAME_DURATION_MS);
	}
}

void BreatheAnimation::GeneratePhase3()
{
	for (size_t i = 0; i < STEPS; ++i)
	{
		Colour colour{};

		const auto val = (180.0f / STEPS) * i;

		// Generate a sine wave for a breathing effect.
		colour[INDEX_COLOUR_BLUE] = 255 * std::sin(val * (MATH_PI / 180.0f));
		colour[INDEX_COLOUR_RED] = 0;
		colour[INDEX_COLOUR_GRAY] = 0;
		colour[INDEX_COLOUR_GREEN] = 0;

		m_frames.AddFrame(Zone::ALL, colour, FRAME_DURATION_MS);
	}
}
void BreatheAnimation::GeneratePhase4()
{
	for (size_t i = 0; i < STEPS; ++i)
	{
		Colour colour{};

		const auto val = (180.0f / STEPS) * i;

		// Generate a sine wave for a breathing effect.
		colour[INDEX_COLOUR_GRAY] = 255 * std::sin(val * (MATH_PI / 180.0f));
		colour[INDEX_COLOUR_BLUE] =
		colour[INDEX_COLOUR_RED] = 0;
		colour[INDEX_COLOUR_GREEN] = 0;

		m_frames.AddFrame(Zone::ALL, colour, FRAME_DURATION_MS);
	}
}
