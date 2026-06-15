// Created by DeviceIoControl

#pragma once

#include "Colour.h"

class ColourFactory
{
public:
	ColourFactory() = default;
	~ColourFactory() = default;

	Colour Create(uint8_t r, uint8_t g, uint8_t b) const;
	Colour Create(uint32_t rgb) const;
};