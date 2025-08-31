// Created by DeviceIoControl

#pragma once

#include "IKeyboardCommunicator.h"

class FakeKeyboardCommunicator 
	: public IKeyboardCommunicator
{
public:
	FakeKeyboardCommunicator() = default;

	bool SendKBCode(uint32_t code) override;

	bool SetKBColour(Zone zone, const Colour& colour) override;

	~FakeKeyboardCommunicator() override = default;
};