// Created by DeviceIoControl

#pragma once

#include "IAnimation.h"
#include "FrameCollection.h"
#include "FramePatternGenerator.h"

class SakuraLavenderAnimation
	: public IAnimation
{
public:
	SakuraLavenderAnimation();

	std::wstring GetName() const override;

	std::optional<Frame> GetFrame(uint32_t idx) override;

	bool IsSupportedKB(KeyboardType kbType) const override;

	uint32_t Size() const override;

	~SakuraLavenderAnimation() override = default;

protected:
	void AddFrame(const Frame& frame) override;

private:
	FrameCollection m_frames{};
	FramePatternGenerator m_patternGenerator{};
};