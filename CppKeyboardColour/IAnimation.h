#pragma once

#include "stdafx.h"
#include "Frame.h"

class IAnimation 
{
public:
	virtual std::optional<Frame> GetFrame(uint32_t idx) = 0;

	virtual bool IsSupportedDevice(uint32_t deviceId) const = 0;

	virtual uint32_t Size() const = 0;

	virtual ~IAnimation() = default;

protected:
	virtual void AddFrame(const Frame& frame) = 0;
};