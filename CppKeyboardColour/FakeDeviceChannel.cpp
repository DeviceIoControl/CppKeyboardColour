// Created by DeviceIoControl

#include "stdafx.h"
#include "FakeDeviceChannel.h"
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
	}

} // namespace

bool FakeDeviceChannel::SendCode(uint32_t code)
{
	uint8_t const zoneIdentifier = static_cast<uint8_t>((code & 0xff000000) >> 24);
	auto const rgbColour = m_colourFactory.Convert(ColourFormat::B8R8G8, code & 0x00ffffff, ColourFormat::R8G8B8);
	auto const colourObject = m_colourFactory.Create(rgbColour);

	if (zoneIdentifier >= 0xf0 && zoneIdentifier <= 0xf2)
	{
		std::cout << "Keyboard Zone: " << static_cast<Zone>(zoneIdentifier) << ", ";
	}

	if (zoneIdentifier == 0xf3)
	{
		std::cout << "Lightbar ";
	}

	if (zoneIdentifier == 0xf4) 
	{
		std::cout << "Logo ";
	}

	std::cout << "Colour: "
		<< "(RED - 0x" << (void*)colourObject[INDEX_COLOUR_RED] << "), "
		<< "(GREEN - 0x" << (void*)colourObject[INDEX_COLOUR_GREEN] << "), "
		<< "(BLUE - 0x" << (void*)colourObject[INDEX_COLOUR_BLUE] << ") \n";

	return true;

}

DeviceChannelType FakeDeviceChannel::QueryType() const 
{
	return DeviceChannelType::Fake;
}