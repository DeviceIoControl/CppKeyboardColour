// Created by DeviceIoControl

#pragma once

#include "stdafx.h"
#include "Colour.h"
#include "DeviceMask.h"

struct Frame
{
	Frame(DeviceMask deviceMask, Zone activeZone, const Colour& zoneColour, uint32_t msTime)
		: devices(deviceMask), zone(activeZone), colour(zoneColour), ms_time(msTime)
	{
	}

	Zone zone;
	Colour colour;
	uint32_t ms_time;
	DeviceMask devices;
};