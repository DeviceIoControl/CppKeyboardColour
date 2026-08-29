// Created by DeviceIoControl

#include "stdafx.h"
#include "SystemAnimationTranslator.h"

SystemAnimation SystemAnimationTranslator::Translate(const std::wstring& sysAnimationAlias) const
{
	const auto upperSysAnimationAlias = xstd::to_upper_case(sysAnimationAlias);
	const auto result = m_animationAliasMap.find(upperSysAnimationAlias);
	return (result != m_animationAliasMap.cend()) ? result->second : SystemAnimation::KB_MODE_CUSTOM;
}