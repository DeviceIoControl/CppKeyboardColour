#include "stdafx.h"
#include "ColourFactory.h"

std::map<std::wstring, Colour> ColourFactory::CreateInitialMap()
{
    std::map<std::wstring, Colour> colours;
    colours[L"red"] = { 255, 0, 0 };
    colours[L"green"] = { 0, 255, 0 };
    colours[L"blue"] = { 0, 0, 255 };
    colours[L"yellow"] = { 255, 255, 0 };
    colours[L"cyan"] = { 0, 255, 255 };
    colours[L"magenta"] = { 255, 0, 255 };
    colours[L"white"] = { 255, 255, 255 };
    colours[L"black"] = { 0, 0, 0 };
    colours[L"orange"] = { 255, 165, 0 };
    colours[L"purple"] = { 128, 0, 128 };
    colours[L"pink"] = { 255, 192, 203 };
    colours[L"brown"] = { 165, 42, 42 };
    colours[L"gray"] = { 128, 128, 128 };
    colours[L"lime"] = { 50, 205, 50 };
    colours[L"gold"] = { 255, 215, 0 };
    colours[L"silver"] = { 192, 192, 192 };
    return colours;
}

// Implements the ColourFactory constructor using the static helper.
ColourFactory::ColourFactory() : m_colours(CreateInitialMap()) {}

// Implements other methods
Colour ColourFactory::Create(uint8_t r, uint8_t g, uint8_t b) const
{
    Colour colour{};
    colour[INDEX_COLOUR_RED] = r;
    colour[INDEX_COLOUR_GREEN] = g;
    colour[INDEX_COLOUR_BLUE] = b;
    return colour;
}

std::optional<Colour> ColourFactory::Create(const std::wstring& name) const
{
    auto it = m_colours.find(name);
    if (it != m_colours.end())
    {
        return it->second;
    }
    return {};
}

std::wstring ColourFactory::GetAvailableColors() const
{
    std::wstring names;
    for (const auto& pair : m_colours)
    {
        names += pair.first + L" ";
    }
    return names;
}