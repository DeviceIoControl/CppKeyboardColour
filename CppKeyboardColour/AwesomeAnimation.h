// Created by DeviceIoControl
#pragma once

#include "IAnimation.h"
#include "FramePatternGenerator.h"
#include "FrameCollection.h"

class AwesomeAnimation 
	: public IAnimation
{
public:
	AwesomeAnimation();
	~AwesomeAnimation() override = default;

	std::wstring GetName() const override;
	std::optional<Frame> GetFrame(uint32_t idx) override;
	bool IsHostSupported(const IHost* pHost) const override;
	uint32_t Size() const override;

private:
	FrameCollection m_frames;
	FramePatternGenerator m_frameGenerator;

	template<typename TAnimation>
	void AddAnimationFrames() 
	{
		std::unique_ptr<IAnimation> pAnimation = std::make_unique<TAnimation>();

		for (size_t i = 0; i < pAnimation->Size(); ++i)
		{
			if (auto frame = pAnimation->GetFrame(i))
			{
				frame->devices |= DeviceMask::Lightbar;
				m_frames.AddFrame(frame.value());
			}
		}
	}
};