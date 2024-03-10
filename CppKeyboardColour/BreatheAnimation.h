#pragma once

#include "Frame.h"
#include "FrameCollection.h"
#include "IAnimation.h"

class BreatheAnimation 
	: public IAnimation
{
public:
	BreatheAnimation();

	std::optional<Frame> GetFrame(uint32_t idx) override;

	bool IsSupportedDevice(uint32_t deviceId) const override;

	uint32_t Size() const override;

	~BreatheAnimation() override = default;

protected:
	void AddFrame(const Frame& frame) override;

private:
	FrameCollection m_frames;

	void GeneratePhase1();
	void GeneratePhase2();
	void GeneratePhase3();
};