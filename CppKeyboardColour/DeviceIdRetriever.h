#pragma once

// Created by DeviceIoControl

#include "stdafx.h"
#include "IKeyboard.h"
#include "DeviceIds.h"

class DeviceIdRetriever
{
public:
	DeviceIdRetriever() = default;

	// IMPORTANT: Hard-coded until we have a stable method of retrieving this.
	uint32_t GetDeviceID()
	{
		return DEVICE_ID_NP50SXX;
		//return DEVICE_ID_P650RS_G;

		// For debugging purposes only.
		// return DEVICE_ID_FAKE;
	}

	~DeviceIdRetriever() = default;

private:
};