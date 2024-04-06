// Created by DeviceIoControl

#pragma once

#include "IKeyboard.h"
#include "IAnimation.h"
#include "ScopedComPtr.h"
#include "SystemAnimation.h"
#include "DeviceIdTranslator.h"

class Keyboard 
	: public IKeyboard
{
public:
	Keyboard();

	void SetColour(uint8_t r, uint8_t g, uint8_t b, Zone zone) override;
	void SysAnimation(SystemAnimation animation) override;
	void PlayAnimation(IAnimation& animation, bool bShouldLoop = true) override;

	KeyboardType GetKBType() const;

	~Keyboard() = default;

private:
	KeyboardType m_kbType;
	DeviceIdTranslator m_translator;
	ScopedComPtr<IWbemClassObject> m_pClevoGetObject;
	ScopedComPtr<IWbemClassObject> m_pDataParameter;

	void SetSingleLedKB(uint8_t r, uint8_t g, uint8_t b);
	void SetTripleLedKB(uint8_t r, uint8_t g, uint8_t b, Zone zone);

	void SetKBLed(uint32_t data);

	std::optional<uint32_t> GetDeviceID() const;

	static std::optional<uint32_t> DoGetDeviceID();

	void DoAnimation(IAnimation& animation);
};
