// Created by DeviceIoControl

#pragma once

#include "Colour.h"

enum class ColourFormat : uint16_t
{
	R8G8B8,
	B8R8G8
};

class ColourFactory
{
public:
	ColourFactory() = default;
	~ColourFactory() = default;

	Colour Create(uint8_t r, uint8_t g, uint8_t b) const;
	Colour Create(uint32_t rgb) const;

	uint32_t Create(ColourFormat dstFormat, const Colour& colour) const;
	uint32_t Convert(ColourFormat srcFormat, uint32_t colour, ColourFormat dstFormat) const;
};