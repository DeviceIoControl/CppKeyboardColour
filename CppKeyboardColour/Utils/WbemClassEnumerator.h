// Created by DeviceIoControl

#pragma once
#include "ScopedComPtr.h"

class WbemClassEnumerator
{
public:
	WbemClassEnumerator(ScopedComPtr<IEnumWbemClassObject> pEnumerator);
	~WbemClassEnumerator() = default;

	bool Skip(uint32_t count = 1);
	ScopedComPtr<IWbemClassObject> Next();
	void Reset();

private:
	ScopedComPtr<IEnumWbemClassObject> m_pEnumerator;
};
