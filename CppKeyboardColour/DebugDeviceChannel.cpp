// Created by DeviceIoControl

#include "stdafx.h"
#include "DebugDeviceChannel.h"
#include "Zone.h"

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

		return _Ostr << "Unknown";
	}

} // namespace

DebugDeviceChannel::DebugDeviceChannel(KeyboardType kbType)
	: m_kbType(kbType)
{
}

bool DebugDeviceChannel::SendCode(uint32_t code)
{
	Zone const zoneIdentifier = static_cast<Zone>((code & 0xff000000) >> 24);
	auto const rgbColour = m_colourFactory.Convert(ColourFormat::B8R8G8, code & 0x00ffffff, ColourFormat::R8G8B8);
	auto const colourObject = m_colourFactory.Create(rgbColour);

	std::cout << "Code: 0x" << (void*)code << " -> ";

	if (m_kbType == KeyboardType::TRIPLE_ZONE)
	{
		if (static_cast<uint8_t>(zoneIdentifier) >= 0xf0 && static_cast<uint8_t>(zoneIdentifier) <= 0xf2) 
		{
			std::cout << "Keyboard Zone: " << static_cast<Zone>(zoneIdentifier) << ", ";
		}
	}

	if (m_kbType == KeyboardType::SINGLE_ZONE)
	{
		std::cout << ((zoneIdentifier == Zone::LEFT) ? "Keyboard Zone: All, " : "");
	}

	if (static_cast<uint8_t>(zoneIdentifier) == 0xf3)
	{
		std::cout << "Lightbar ";
	}

	if (static_cast<uint8_t>(zoneIdentifier) == 0xf4)
	{
		std::cout << "Logo ";
	}

	std::cout << "Colour: "
		<< "(RED - 0x" << (void*)colourObject[INDEX_COLOUR_RED] << "), "
		<< "(GREEN - 0x" << (void*)colourObject[INDEX_COLOUR_GREEN] << "), "
		<< "(BLUE - 0x" << (void*)colourObject[INDEX_COLOUR_BLUE] << ") \n";

	return true;

}

DeviceChannelType DebugDeviceChannel::QueryType() const
{
	return DeviceChannelType::Debug;
}