// Created by DeviceIoControl

#pragma once

#include "stdafx.h"
#include "IAnimation.h"
#include "KeyboardType.h"

class IKeyboard
{
public:
	virtual void SendCode(uint32_t code) = 0;
	virtual void SetColour(uint8_t r, uint8_t g, uint8_t b, Zone zone) = 0;
	virtual void SetBacklightOff() = 0;
	virtual void SetBacklightOn() = 0;
	virtual void PlayAnimation(IAnimation& animation, bool bShouldLoop) = 0;
	virtual KeyboardType GetKBType() const = 0;

	virtual ~IKeyboard() = default;
};