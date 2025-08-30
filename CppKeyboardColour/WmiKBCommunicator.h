// Created by DeviceIoControl

#pragma once

#include "ScopedComPtr.h"
#include "IKeyboardCommunicator.h"

class WmiKBCommunicator
	: public IKeyboardCommunicator
{
public:
	WmiKBCommunicator();

	bool SetKeyboardColour(Zone zone, const Colour& colour) override;

	bool SendKeyboardData(uint32_t data) override;

	~WmiKBCommunicator() = default;

private:
	ScopedComPtr<IWbemClassObject> m_pDataParameter;
	ScopedComPtr<IWbemClassObject> m_pClevoGetObject;
};