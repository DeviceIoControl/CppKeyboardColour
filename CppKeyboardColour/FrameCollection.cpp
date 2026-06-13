// Created by DeviceIoControl

#include "stdafx.h"
#include "FrameCollection.h"

FrameCollection::FrameCollection(const std::vector<Frame>& frames)
	: m_frames(frames)
{
}

void FrameCollection::AddFrame(const Frame& frame)
{
	m_frames.push_back(frame);
}

void FrameCollection::AddFrame(Zone activeZone, Colour zoneColour, uint32_t msTime)
{
	m_frames.emplace_back(activeZone, zoneColour, msTime);
}

void FrameCollection::AddFrames(const FrameCollection& frames)
{
	std::copy(frames.m_frames.cbegin(), frames.m_frames.cend(), std::back_inserter(m_frames));
}

std::optional<Frame> FrameCollection::GetFrame(uint32_t idx)
{
	return (m_frames.size() >= idx) ? std::make_optional(m_frames[idx]) : std::nullopt;
}

