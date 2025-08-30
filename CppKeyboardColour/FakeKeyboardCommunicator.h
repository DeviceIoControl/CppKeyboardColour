// Created by DeviceIoControl

#pragma once

#include "IKeyboardCommunicator.h"

class FakeKeyboardCommunicator 
	: public IKeyboardCommunicator
{
public:
	FakeKeyboardCommunicator() = default;

	bool SendKeyboardData(uint32_t data) override;

	bool SetKeyboardColour(Zone zone, const Colour& colour) override;

	~FakeKeyboardCommunicator() override = default;
};