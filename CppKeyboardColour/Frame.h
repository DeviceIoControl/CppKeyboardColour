#pragma once

#include "stdafx.h"
#include "Colour.h"

struct Frame
{
	Frame(Zone activeZone, Colour zoneColour, uint32_t msTime) 
		: zone(activeZone), colour(zoneColour), ms_time(msTime)
	{
	}

	Zone zone;
	Colour colour;
	uint32_t ms_time;
};