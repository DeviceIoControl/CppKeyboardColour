// Created by DeviceIoControl

#include "stdafx.h"
#include "WbemClassEnumerator.h"

#define ENUM_TIMEOUT -1

WbemClassEnumerator::WbemClassEnumerator(ScopedComPtr<IEnumWbemClassObject> pEnumerator) 
	: m_pEnumerator(std::move(pEnumerator))
{
}

bool WbemClassEnumerator::Skip(uint32_t count /*= 1*/)
{
	return SUCCEEDED(m_pEnumerator->Skip(ENUM_TIMEOUT, count));
}

ScopedComPtr<IWbemClassObject> WbemClassEnumerator::Next() 
{
	ULONG ulReturned = 0;
	IWbemClassObject* pWbemClassObject = nullptr;

	m_pEnumerator->Next(ENUM_TIMEOUT, 1, &pWbemClassObject, &ulReturned);
	
	return ScopedComPtr<IWbemClassObject>(pWbemClassObject);
}

void WbemClassEnumerator::Reset() 
{
	m_pEnumerator->Reset();
}
