// Created by DeviceIoControl

#include "stdafx.h"
#include "ComInitialiser.h"

ComInitialiser::ComInitialiser(COINIT coInit /*= COINIT::COINIT_APARTMENTTHREADED*/)
{
	CoInitializeEx(nullptr, coInit);
}

ComInitialiser::~ComInitialiser()
{
	CoUninitialize();
}