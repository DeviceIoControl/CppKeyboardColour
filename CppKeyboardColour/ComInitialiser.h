// Created by DeviceIoControl

#pragma once

class ComInitialiser 
{
public:
	ComInitialiser(COINIT coInit = COINIT::COINIT_APARTMENTTHREADED);
	~ComInitialiser();
};