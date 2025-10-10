//Created by BenRango

#pragma once

#include "IAnimation.h"
#include "FrameCollection.h"


class SingleColourBreatheAnimation : public IAnimation
{
public:
    SingleColourBreatheAnimation(const Colour& targetColour);

    std::wstring GetName() const override;

    std::optional<Frame> GetFrame(uint32_t idx) override;

    bool IsSupportedKB(KeyboardType kbType) const override;

    uint32_t Size() const override;

private:
    FrameCollection m_frames;

    void AddFrame(const Frame& frame);

    void GenerateBreathe(const Colour& targetColour, uint32_t steps, uint32_t stepTimeMs);
};