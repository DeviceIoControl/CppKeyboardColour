// Created by DeviceIoControl

#pragma once

#include "stdafx.h"
#include "Frame.h"

class IHost;

class IAnimation
{
public:
	virtual std::wstring GetName() const = 0;

	virtual std::optional<Frame> GetFrame(uint32_t idx) = 0;

	virtual bool IsHostSupported(const IHost* pHost) const = 0;

	virtual uint32_t Size() const = 0;

	virtual ~IAnimation() = default;
};