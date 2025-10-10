#pragma once

#include "stdafx.h"
#include "Frame.h"
#include "KeyboardType.h"

class IAnimation 
{
public:

	virtual std::wstring GetName() const = 0;

	virtual std::optional<Frame> GetFrame(uint32_t idx) = 0;

	virtual bool IsSupportedKB(KeyboardType kbType) const = 0;

	virtual uint32_t Size() const = 0;

	virtual ~IAnimation() = default;

protected:
	virtual void AddFrame(const Frame& frame) = 0;
};