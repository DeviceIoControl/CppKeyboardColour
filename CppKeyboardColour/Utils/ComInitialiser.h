// Created by DeviceIoControl

#pragma once

class ComInitialiser 
{
public:
	explicit ComInitialiser(COINIT coInit = COINIT::COINIT_APARTMENTTHREADED);
	~ComInitialiser();

	bool InitialiseSecurity(DWORD dwAuthnLevel, DWORD dwImpLevel);
};