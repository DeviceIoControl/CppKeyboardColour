// Created by DeviceIoControl
#pragma once

#include "IAnimation.h"
#include "FramePatternGenerator.h"
#include "FrameCollection.h"
#include "ColourFactory.h"
#include "IHost.h"

class ColourWaveAnimation 
	: public IAnimation
{
public:
	ColourWaveAnimation();
	~ColourWaveAnimation() override = default;

	std::wstring GetName() const override;

	std::optional<Frame> GetFrame(uint32_t idx) override;

	 bool IsHostSupported(const IHost* pHost) const override;

	 uint32_t Size() const override;

private:
	ColourFactory m_factory;
	FrameCollection m_frames;
	FramePatternGenerator m_frameGenerator;
};