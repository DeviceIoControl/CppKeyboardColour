// Created by DeviceIoControl

#pragma once

#include "ScopedComPtr.h"
#include "FakeKeyboardCommunicator.h"
#include "ColourFactory.h"
#include "KeyboardType.h"
#include "IKeyboardCommunicator.h"
#include "WbemService.h"

class WmiKBCommunicator
	: public IKeyboardCommunicator
{
public:
	WmiKBCommunicator(KeyboardType kbType);
	~WmiKBCommunicator() = default;

	bool SetKBColour(Zone zone, const Colour& colour) override;
	bool SendKBCode(uint32_t code) override;
	bool SetLightbarColour(const Colour& colour) override;

private:
	KeyboardType m_kbType;
	WbemService m_wbemService{};
	ColourFactory m_colourFactory{};
	ScopedComPtr<IWbemClassObject> m_pDataParameter;
	ScopedComPtr<IWbemClassObject> m_pClevoGetObject;

	bool SetKBZoneColour(Zone zone, const Colour& colour);
	bool SetFullKBColour(const Colour& colour);
};