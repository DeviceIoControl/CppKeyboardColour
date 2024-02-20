// Created by DeviceIoControl

#pragma once

#include "Frame.h"

class Animation
{
public:
	Animation() = default;

	explicit Animation(const std::vector<Frame>& frames);
	void addFrame(const Frame& frame);
	std::optional<Frame> getFrame(uint32_t idx);

	inline uint32_t size() const { return m_frames.size(); }
	
	~Animation() = default;

private:
	uint32_t m_Position = 0;
	std::vector<Frame> m_frames;
};