// Created by DeviceIoControl

#include "stdafx.h"
#include "LogoDevice.h"
#include "KeyboardType.h"
#include "DeviceMask.h"

LogoDevice::LogoDevice(std::shared_ptr<IDeviceChannel> pDeviceChannel) 
	: m_pDevChannel(std::move(pDeviceChannel))
{
}

bool LogoDevice::SetColour(Zone zone, const Colour& colour) 
{
	// Logo = 0xF4
	return (zone == Zone::ALL) ? m_pDevChannel->SendCode((0xF4 << 24ul) | m_colourFactory.Create(colour)) : false;
}

uint64_t LogoDevice::Query(QueryType queryType) 
{
	switch (queryType)
	{
	case QueryType::KeyboardType:
		return xstd::to_underlying(KeyboardType::NONE);

	case QueryType::DeviceType:
		return xstd::to_underlying(DeviceMask::Logo);

	case QueryType::DeviceChannelType:
		return xstd::to_underlying(m_pDevChannel->QueryType());
	}
}

bool LogoDevice::SendCode(uint32_t code) 
{
	return m_pDevChannel->SendCode(code);
}
