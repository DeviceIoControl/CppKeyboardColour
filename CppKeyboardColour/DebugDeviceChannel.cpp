// Created by DeviceIoControl

#include "stdafx.h"
#include "DebugDeviceChannel.h"
#include "Zone.h"

namespace
{
	std::string_view GetZoneString(KeyboardType kbType, uint32_t code)
	{
		switch ((code & 0xff000000) >> 24)
		{
		case xstd::to_underlying(Zone::LEFT):
			return (kbType == KeyboardType::SINGLE_ZONE) ? "Keyboard Zone: All," : "Keyboard Zone: Left,";

		case xstd::to_underlying(Zone::MID):
			return "Keyboard Zone: Middle,";

		case xstd::to_underlying(Zone::RIGHT):
			return "Keyboard Zone: Right,";

		case 0xF3:
			return "Lightbar,";

		case 0xF4:
			return "Logo,";
		}
	}
} // namespace

DebugDeviceChannel::DebugDeviceChannel(KeyboardType kbType)
	: m_kbType(kbType)
{
}

bool DebugDeviceChannel::SendCode(uint32_t code)
{
	const auto rgbColour = m_colourFactory.Convert(ColourFormat::B8R8G8, code & 0x00ffffff, ColourFormat::R8G8B8);
	const auto colourObject = m_colourFactory.Create(rgbColour);

	std::printf("Code: 0x%08X -> %s Colour: (RED: 0x%08X), (GREEN: 0x%08X), (BLUE: 0x%08X)\n", 
		code, 
		GetZoneString(m_kbType, code).data(),
		colourObject[INDEX_COLOUR_RED],
		colourObject[INDEX_COLOUR_GREEN],
		colourObject[INDEX_COLOUR_BLUE]);

	return true;
}

DeviceChannelType DebugDeviceChannel::QueryType() const
{
	return DeviceChannelType::Debug;
}