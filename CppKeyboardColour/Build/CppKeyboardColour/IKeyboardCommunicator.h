// Created by DeviceIoControl

#pragma once

#include "stdafx.h"

#include "Zone.h"
#include "Colour.h"

class IKeyboardCommunicator
{
public:
	virtual bool SendKBCode(uint32_t code) = 0;
	virtual bool SetKBColour(Zone zone, const Colour& colour) = 0;

	virtual ~IKeyboardCommunicator() = default;
};

using IKeyboardCommunicatorPtr = std::shared_ptr<IKeyboardCommunicator>;