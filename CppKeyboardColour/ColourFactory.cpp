// Created by DeviceIoControl

#include "stdafx.h"
#include "ColourFactory.h"

Colour ColourFactory::Create(uint8_t r, uint8_t g, uint8_t b) const
{
	Colour colour{};
	colour[INDEX_COLOUR_RED] = r;
	colour[INDEX_COLOUR_GREEN] = g;
	colour[INDEX_COLOUR_BLUE] = b;

	return colour;
}