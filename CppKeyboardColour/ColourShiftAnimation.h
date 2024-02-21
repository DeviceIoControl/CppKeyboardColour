#pragma once

#include "IAnimation.h"
#include "FrameCollection.h"

class ColourShiftAnimation 
	: public IAnimation
{
public:
	ColourShiftAnimation();

	void AddFrame(const Frame& frame) override;
	std::optional<Frame> GetFrame(uint32_t idx) override;

	bool IsSupportedBoard(uint32_t boardId) override;

	uint32_t Size() const override;

	~ColourShiftAnimation() override = default;

private:
	FrameCollection m_frames;

	void GeneratePhase1(uint8_t(&rgb)[3][3]);
	void GeneratePhase2(uint8_t(&rgb)[3][3]);
	void GeneratePhase3(uint8_t(&rgb)[3][3]);

	void GenerateIntermediateFrame(const Frame& frame);
};
