#pragma once

#include "stdafx.h"

#include "Zone.h"
#include "Colour.h"

class IKeyboardCommunicator
{
public:
	virtual bool SendKeyboardData(uint32_t data) = 0;
	virtual bool SetKeyboardColour(Zone zone, const Colour& colour) = 0;

	virtual ~IKeyboardCommunicator() = default;
};

using IKeyboardCommunicatorPtr = std::shared_ptr<IKeyboardCommunicator>;