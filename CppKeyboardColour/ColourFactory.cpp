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

Colour ColourFactory::Create(uint32_t rgb) const 
{
	Colour colour;

	colour[INDEX_COLOUR_RED] = static_cast<uint8_t>((rgb & 0x00FF0000) >> 16);
	colour[INDEX_COLOUR_GREEN] = static_cast<uint8_t>((rgb & 0x0000FF00) >> 8);
	colour[INDEX_COLOUR_BLUE] = static_cast<uint8_t>(rgb & 0x000000FF);

	return colour;
}