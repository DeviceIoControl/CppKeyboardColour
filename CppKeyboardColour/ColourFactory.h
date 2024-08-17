#pragma once

#include "stdafx.h"
#include "Colour.h"

class ColourFactory
{
public:
	ColourFactory() = default;
	~ColourFactory() = default;

	Colour Create(uint8_t r, uint8_t g, uint8_t b) const
	{
		Colour colour{};
		colour[INDEX_COLOUR_RED] = r;
		colour[INDEX_COLOUR_GREEN] = g;
		colour[INDEX_COLOUR_BLUE] = b;

		return colour;
	}
};