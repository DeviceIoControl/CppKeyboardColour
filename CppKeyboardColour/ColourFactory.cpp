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

uint32_t ColourFactory::Create(ColourFormat dstFormat, const Colour& colour) const
{
	switch (dstFormat)
	{
	case ColourFormat::B8R8G8:
		return static_cast<uint32_t>((colour[INDEX_COLOUR_BLUE] << 16ul) | (colour[INDEX_COLOUR_RED] << 8ul) | colour[INDEX_COLOUR_GREEN]);

	case ColourFormat::R8G8B8:
		return static_cast<uint32_t>((colour[INDEX_COLOUR_RED] << 16ul) | (colour[INDEX_COLOUR_GREEN] << 8ul) | colour[INDEX_COLOUR_BLUE]);
	}

	return 0;
}

uint32_t ColourFactory::Convert(ColourFormat srcFormat, uint32_t colour, ColourFormat dstFormat) const
{
	Colour colourObj{};

	switch (srcFormat)
	{
	case ColourFormat::B8R8G8:
		colourObj[INDEX_COLOUR_BLUE] = static_cast<uint8_t>((colour & 0x00ff0000) >> 16);
		colourObj[INDEX_COLOUR_RED] = static_cast<uint8_t>((colour & 0x0000ff00) >> 8);
		colourObj[INDEX_COLOUR_GREEN] = static_cast<uint8_t>(colour & 0x000000ff);
		break;

	case ColourFormat::R8G8B8:
		colourObj[INDEX_COLOUR_RED] = static_cast<uint8_t>((colour & 0x00ff0000) >> 16);
		colourObj[INDEX_COLOUR_GREEN] = static_cast<uint8_t>((colour & 0x0000ff00) >> 8);
		colourObj[INDEX_COLOUR_BLUE] = static_cast<uint8_t>(colour & 0x000000ff);
		break;
	}

	return this->Create(dstFormat, colourObj);
}
