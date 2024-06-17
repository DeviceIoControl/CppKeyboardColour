#pragma once

#include "stdafx.h"
#include "IKeyboard.h"
#include "DeviceIds.h"

class DeviceIdRetriever
{
public:
	DeviceIdRetriever() = default;

	uint32_t GetDeviceID() 
	{
		return DEVICE_ID_NP50SXX;
	} 

	~DeviceIdRetriever() = default;

private:
};