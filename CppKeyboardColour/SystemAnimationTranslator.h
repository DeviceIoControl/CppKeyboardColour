// Created by DeviceIoControl

#pragma once
#include "SystemAnimation.h"

class SystemAnimationTranslator
{
public:
	SystemAnimationTranslator() = default;
	~SystemAnimationTranslator() = default;

	SystemAnimation Translate(const std::wstring& sysAnimationAlias) const;

private:
	std::map<std::wstring, SystemAnimation> const m_animationAliasMap
	{
		{L"KB_MODE_BREATHE", SystemAnimation::KB_MODE_BREATHE},
		{L"KB_MODE_CYCLE", SystemAnimation::KB_MODE_CYCLE},
		{L"KB_MODE_DANCE", SystemAnimation::KB_MODE_DANCE},
		{L"KB_MODE_FLASH", SystemAnimation::KB_MODE_FLASH},
		{L"KB_MODE_TEMPO", SystemAnimation::KB_MODE_TEMPO},
		{L"KB_MODE_WAVE", SystemAnimation::KB_MODE_WAVE},
		{L"KB_MODE_RANDOM_COLOUR", SystemAnimation::KB_MODE_RANDOM_COLOUR}
	};
};