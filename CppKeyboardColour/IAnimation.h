#pragma once

#include "stdafx.h"
#include "Frame.h"

class IAnimation 
{
public:
	virtual void AddFrame(const Frame& frame) = 0;
	virtual std::optional<Frame> GetFrame(uint32_t idx) = 0;

	virtual bool IsSupportedBoard(uint32_t boardId) = 0;

	virtual uint32_t Size() const = 0;

	virtual ~IAnimation() = default;
};