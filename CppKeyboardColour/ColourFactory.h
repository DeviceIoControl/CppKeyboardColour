// Created by DeviceIoControl

#pragma once
#include "Colour.h"

enum class ColourFormat : uint16_t
{
	R8G8B8,
	B8R8G8
};

enum class ColourValue : uint32_t 
{ 
	RED = 0xff0000,
	GREEN = 0x00ff00,
	BLUE = 0x0000ff,
	YELLOW = 0xffff00,
	PURPLE = 0xff00ff,
	WHITE = 0xffffff,
	BLACK = 0x000000
};

class ColourFactory
{
public:
	ColourFactory() = default;
	~ColourFactory() = default;

	Colour Create(uint8_t r, uint8_t g, uint8_t b) const;
	Colour Create(uint32_t rgb) const;
	Colour Create(ColourValue colour) const;

	uint32_t Create(ColourFormat dstFormat, const Colour& colour) const;
	uint32_t Convert(ColourFormat srcFormat, uint32_t colour, ColourFormat dstFormat) const;
};