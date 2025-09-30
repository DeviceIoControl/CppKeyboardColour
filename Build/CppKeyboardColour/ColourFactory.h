#pragma once

#include "stdafx.h"
#include "Colour.h"
#include <map>
#include <string>
#include <vector>
#include <optional>
#include <utility>
#include <cstdint>

class ColourFactory
{
public:
	ColourFactory();

	Colour Create(uint8_t r, uint8_t g, uint8_t b) const;
	std::optional<Colour> Create(const std::wstring& name) const;
	std::wstring GetAvailableColors() const;

private:
	// A map to store named colors. It's populated by a static helper function.
	std::map<std::wstring, Colour> m_colours;

	// A static helper function to create and return the map of colors.
	static std::map<std::wstring, Colour> CreateInitialMap();
};