#pragma once

#include "IAnimation.h"
#include "KeyboardType.h"
#include "FrameCollection.h"
#include "DeviceIdTranslator.h"

class ColourShiftAnimation 
	: public IAnimation
{
public:
	ColourShiftAnimation();

	std::optional<Frame> GetFrame(uint32_t idx) override;

	// This animation requires 3-Zone keyboards.
	bool IsSupportedKB(KeyboardType kbType) const override;

	uint32_t Size() const override;

	~ColourShiftAnimation() override = default;

protected:
	void AddFrame(const Frame& frame) override;

private:
	FrameCollection m_frames;
	
	void GeneratePhase1(uint8_t(&rgb)[3][3]);
	void GeneratePhase2(uint8_t(&rgb)[3][3]);
	void GeneratePhase3(uint8_t(&rgb)[3][3]);

	void GenerateDelayFrame(const Frame& frame);
};
