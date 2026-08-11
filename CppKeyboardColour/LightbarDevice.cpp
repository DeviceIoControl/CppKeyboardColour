// Created by DeviceIoControl

#include "stdafx.h"
#include "LightbarDevice.h"
#include "KeyboardType.h"
#include "DeviceMask.h"

LightbarDevice::LightbarDevice(std::shared_ptr<IDeviceChannel> pDeviceChannel) 
	: m_pDevChannel(std::move(pDeviceChannel))
{
}

bool LightbarDevice::SetColour(Zone zone, const Colour& colour)
{
	// Lightbar = 0xF3
	return (zone == Zone::ALL && m_pDevChannel) ? m_pDevChannel->SendCode((0xF3 << 24ul) | m_colourFactory.Create(colour)) : false;
}

uint64_t LightbarDevice::Query(QueryType queryType) 
{
	switch (queryType) 
	{
	case QueryType::KeyboardType:
		return xstd::to_underlying(KeyboardType::NONE);

	case QueryType::DeviceType:
		return xstd::to_underlying(DeviceMask::Lightbar);

	case QueryType::DeviceChannelType:
		return (m_pDevChannel) ? xstd::to_underlying(m_pDevChannel->QueryType()) : 0;
	}

	return 0;
}

bool LightbarDevice::SendCode(uint32_t code) 
{
	return (m_pDevChannel) ? m_pDevChannel->SendCode(code) : false;
}