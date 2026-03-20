// Created by DeviceIoControl

#include "stdafx.h"
#include "SystemAnimationTranslator.h"
#include "ExtendedStl.h"

SystemAnimation SystemAnimationTranslator::Translate(const std::wstring& sysAnimationAlias) const
{
	auto const upperSysAnimationAlias = xstd::to_upper_case(sysAnimationAlias);
	auto const result = m_animationAliasMap.find(upperSysAnimationAlias);
	return (result != m_animationAliasMap.cend()) ? result->second : SystemAnimation::KB_MODE_CUSTOM;
}