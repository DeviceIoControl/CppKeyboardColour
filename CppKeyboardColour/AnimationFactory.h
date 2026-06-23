// Created by DeviceIoControl

#pragma once
#include "IAnimation.h"

class AnimationFactory 
{
public:
	AnimationFactory() = default;
	~AnimationFactory() = default;

	std::unique_ptr<IAnimation> Create(const std::wstring& name) const;
};