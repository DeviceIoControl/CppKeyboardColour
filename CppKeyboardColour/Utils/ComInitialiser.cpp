// Created by DeviceIoControl

#include "stdafx.h"
#include "ComInitialiser.h"
#include "../Console/Logger.h"

ComInitialiser::ComInitialiser(COINIT coInit /*= COINIT::COINIT_APARTMENTTHREADED*/)
{
	const auto hr = CoInitializeEx(nullptr, coInit);

	if (FAILED(hr)) 
	{
		KB_ERROR_STATUS(L"CoInitialize", hr);
	}
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