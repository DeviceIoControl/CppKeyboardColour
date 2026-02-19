// Created by DeviceIoControl

#pragma once

#include "Frame.h"
#include "FrameCollection.h"
#include "ColourFactory.h"
#include "IAnimation.h"

class BreatheAnimation 
	: public IAnimation
{
public:
	BreatheAnimation();

	std::wstring GetName() const override;

	std::optional<Frame> GetFrame(uint32_t idx) override;

	bool IsSupportedKB(KeyboardType kbType) const override;

	uint32_t Size() const override;

	~BreatheAnimation() override = default;

protected:
	void AddFrame(const Frame& frame) override;

private:
	FrameCollection m_frames;
	ColourFactory m_factory{};
	
	void GeneratePhase1();
	void GeneratePhase2();
	void GeneratePhase3();
};