// Created by DeviceIoControl

#pragma once

#include "Frame.h"

class FrameCollection
{
public:
	FrameCollection() = default;

	explicit FrameCollection(const std::vector<Frame>& frames);
	void AddFrame(const Frame& frame);
	void AddFrame(Zone activeZone, Colour zoneColour, uint32_t msTime);
	std::optional<Frame> GetFrame(uint32_t idx);

	inline uint32_t Size() const { return m_frames.size(); }
	
	~FrameCollection() = default;

private:
	uint32_t m_Position = 0;
	std::vector<Frame> m_frames;
};