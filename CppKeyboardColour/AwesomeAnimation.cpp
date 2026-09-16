// Created by DeviceIoControl

#ifndef _AWESOME_ANIMATION_H_
#define _AWESOME_ANIMATION_H_
#endif

#include "stdafx.h"
#include "AwesomeAnimation.h"
#include "Animations.h"

AwesomeAnimation::AwesomeAnimation()
{
	this->AddAnimationFrames<BreatheAnimation>();
	this->AddAnimationFrames<FreshBreatheAnimation>();
	this->AddAnimationFrames<ColourTransformAnimation>();
	this->AddAnimationFrames<PulsatingBlinkAnimation>();
	this->AddAnimationFrames<HeartbeatAnimation>();
	this->AddAnimationFrames<SakuraTransformAnimation>();
	this->AddAnimationFrames<PinkBreatheAnimation>();
	this->AddAnimationFrames<SunsetBreatheAnimation>();
	this->AddAnimationFrames<SakuraSunsetAnimation>();
}

std::wstring AwesomeAnimation::GetName() const
{
	return L"Awesome";
}

std::optional<Frame> AwesomeAnimation::GetFrame(uint32_t idx)
{
	return m_frames.GetFrame(idx);
}

bool AwesomeAnimation::IsHostSupported(const IHost* pHost) const
{
	return (pHost) ? pHost->GetKeyboardType() != KeyboardType::PER_KEY : false;
}

uint32_t AwesomeAnimation::Size() const
{
	return m_frames.Size();
}