// Created by DeviceIoControl

#include "stdafx.h"
#include "Animation.h"

Animation::Animation(const std::vector<Frame>& frames)
	: m_frames(frames)
{
}

void Animation::addFrame(const Frame& frame)
{
	m_frames.push_back(frame);
}

std::optional<Frame> Animation::getFrame(uint32_t idx)
{
	return (m_frames.size() >= idx) ? std::make_optional(m_frames[idx]) : std::nullopt;
}