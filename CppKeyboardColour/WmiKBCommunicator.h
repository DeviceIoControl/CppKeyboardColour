// Created by DeviceIoControl

#pragma once

#include "ScopedComPtr.h"
#include "IKeyboardCommunicator.h"

class WmiKBCommunicator
	: public IKeyboardCommunicator
{
public:
	WmiKBCommunicator();
	~WmiKBCommunicator() = default;

	bool SetKBColour(Zone zone, const Colour& colour) override;
	bool SendKBCode(uint32_t code) override;

private:
	ScopedComPtr<IWbemClassObject> m_pDataParameter;
	ScopedComPtr<IWbemClassObject> m_pClevoGetObject;
};