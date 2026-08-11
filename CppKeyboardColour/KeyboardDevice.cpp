// Created by DeviceIoControl

#include "stdafx.h"
#include "KeyboardDevice.h"
#include "DeviceMask.h"

namespace
{
	std::ostream& operator<<(std::ostream& _Ostr, Zone zone)
	{
		switch (zone)
		{
		case Zone::LEFT:
			return _Ostr << "Left";

		case Zone::MID:
			return _Ostr << "Middle";

		case Zone::RIGHT:
			return _Ostr << "Right";
		}
	}

} // namespace

KeyboardDevice::KeyboardDevice(KeyboardType kbType, std::shared_ptr<IDeviceChannel> pDeviceChannel)
	: m_kbType(kbType),
	m_pDevChannel(std::move(pDeviceChannel))
{
}

bool KeyboardDevice::SetColour(Zone zone, const Colour& colour)
{
	// Callers must always address "ALL" zones on a single-zone keyboard.
	if (m_kbType == KeyboardType::SINGLE_ZONE && zone != Zone::ALL)
	{
		return false;
	}

	return (zone != Zone::ALL) ? this->SetKBZoneColour(zone, colour) : this->SetFullKBColour(colour);
}

uint64_t KeyboardDevice::Query(QueryType queryType)
{
	switch (queryType)
	{
	case QueryType::DeviceChannelType:
		return (m_pDevChannel) ? xstd::to_underlying(m_pDevChannel->QueryType()) : 0;

	case QueryType::DeviceType:
		return xstd::to_underlying(DeviceMask::Keyboard);

	case QueryType::KeyboardType:
		return xstd::to_underlying(m_kbType);
	}
}

bool KeyboardDevice::SendCode(uint32_t code)
{
	return (m_pDevChannel) ? m_pDevChannel->SendCode(code) : false;
}

bool KeyboardDevice::SetKBZoneColour(Zone zone, const Colour& colour)
{
	if (m_kbType == KeyboardType::NONE)
	{
		return false;
	}

	if (m_kbType == KeyboardType::FAKE)
	{
		std::cout << "Zone: " << zone << ", Colour: "
			<< "(RED - 0x" << (void*)colour[INDEX_COLOUR_RED] << "), "
			<< "(GREEN - 0x" << (void*)colour[INDEX_COLOUR_GREEN] << "), "
			<< "(BLUE - 0x" << (void*)colour[INDEX_COLOUR_BLUE] << ") \n\n";

		return true;
	}

	return (m_pDevChannel) ? m_pDevChannel->SendCode((xstd::to_underlying(zone) << 24ul) | m_colourFactory.Create(ColourFormat::B8R8G8, colour)) : false;
}

bool KeyboardDevice::SetFullKBColour(const Colour& colour)
{
	if (m_kbType == KeyboardType::SINGLE_ZONE)
	{
		// Left zone addresses the entire keyboard (Single-Zone).
		return this->SetKBZoneColour(Zone::LEFT, colour);
	}

	for (auto const currentZone : { Zone::LEFT, Zone::MID, Zone::RIGHT })
	{
		// Not worth checking for success here.
		std::ignore = this->SetKBZoneColour(currentZone, colour);
	}

	return true;
}