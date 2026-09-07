// Created by DeviceIoControl

#include "stdafx.h"
#include "ComInitialiser.h"

ComInitialiser::ComInitialiser(COINIT coInit /*= COINIT::COINIT_APARTMENTTHREADED*/)
{
	CoInitializeEx(nullptr, coInit);
}

bool ComInitialiser::InitialiseSecurity(DWORD dwAuthnLevel, DWORD dwImpLevel)
{
	const auto hError = CoInitializeSecurity(
		nullptr,
		-1,
		nullptr,
		nullptr,
		dwAuthnLevel,
		dwImpLevel,
		nullptr,
		EOAC_NONE,
		nullptr);

	return SUCCEEDED(hError);
}

ComInitialiser::~ComInitialiser()
{
	CoUninitialize();
}