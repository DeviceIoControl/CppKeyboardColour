// Created by DeviceIoControl

#pragma once

#include "IAnimation.h"
#include "FrameCollection.h"
#include "FramePatternGenerator.h"
#include "ColourFactory.h"
#include "IHost.h"

class ColourShiftAnimation 
	: public IAnimation
{
public:
	ColourShiftAnimation();

	std::wstring GetName() const override;

	std::optional<Frame> GetFrame(uint32_t idx) override;

	// This animation requires 3-Zone keyboards.
	bool IsHostSupported(const IHost* pHost) const override;

	uint32_t Size() const override;

	~ColourShiftAnimation() override = default;

private:
	FrameCollection m_frames;
	ColourFactory m_factory{};
	FramePatternGenerator m_frameGenerator;
};