// Created by DeviceIoControl

#pragma once

#include "ScopedComPtr.h"
#include "IKeyboardCommunicator.h"
#include "WbemService.h"

class WmiKBCommunicator
	: public IKeyboardCommunicator
{
public:
	WmiKBCommunicator();
	~WmiKBCommunicator() = default;

	bool SetKBColour(Zone zone, const Colour& colour) override;
	bool SendKBCode(uint32_t code) override;

private:
	WbemService m_wbemService{};
	ScopedComPtr<IWbemClassObject> m_pDataParameter;
	ScopedComPtr<IWbemClassObject> m_pClevoGetObject;

	bool SetKBZoneColour(Zone zone, const Colour& colour);
};