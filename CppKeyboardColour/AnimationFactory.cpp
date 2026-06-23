// Created by DeviceIoControl

#include "stdafx.h"
#include "AnimationFactory.h"
#include "Animations.h"

std::unique_ptr<IAnimation> AnimationFactory::Create(const std::wstring& name) const
{
	if (name == L"breathe")
	{
		return std::make_unique<BreatheAnimation>();
	}
	else if (name == L"colourshift")
	{
		return std::make_unique<ColourShiftAnimation>();
	}
	else if (name == L"freshbreathe")
	{
		return std::make_unique<FreshBreatheAnimation>();
	}
	else if (name == L"colourtransform")
	{
		return std::make_unique<ColourTransformAnimation>();
	}
	else if (name == L"blink")
	{
		return std::make_unique<PulsatingBlinkAnimation>();
	}
	else if (name == L"heartbeat")
	{
		return std::make_unique<HeartbeatAnimation>();
	}
	else if (name == L"sakuratransform")
	{
		return std::make_unique<SakuraTransformAnimation>();
	}
	else if (name == L"pinkbreathe")
	{
		return std::make_unique<PinkBreatheAnimation>();
	}
	else if (name == L"sunsetbreathe")
	{
		return std::make_unique<SunsetBreatheAnimation>();
	}
	else if (name == L"sakurasunset")
	{
		return std::make_unique<SakuraSunsetAnimation>();
	}

	return nullptr;
}