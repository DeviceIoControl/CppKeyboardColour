// Created by DeviceIoControl

#pragma once

#include "FrameCollection.h"
#include "IAnimation.h"

class HeartbeatAnimation
	: public IAnimation
{
public:
	HeartbeatAnimation();
	~HeartbeatAnimation() override = default;

	std::wstring GetName() const override;

	std::optional<Frame> GetFrame(uint32_t idx) override;

	bool IsSupportedKB(KeyboardType kbType) const override;

	uint32_t Size() const override;

private:
	FrameCollection m_frames{};

	void AddFrame(const Frame& frame) override;

	void GeneratePulse(const Colour& targetColour, uint32_t beatTimeMs);
};