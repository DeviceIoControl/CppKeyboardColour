// Created by DeviceIoControl

#pragma once

#include "IDevice.h"
#include "IDeviceChannel.h"
#include "Zone.h"
#include "Colour.h"
#include "ColourFactory.h"

class LogoDevice 
	: public IDevice
{
public:
	LogoDevice(std::shared_ptr<IDeviceChannel> pDeviceChannel);
	~LogoDevice() override = default;

	bool SetColour(Zone zone, const Colour& colour) override;
	uint64_t Query(QueryType queryType) override;
	bool SendCode(uint32_t code) override;
	std::wstring GetName() const override;

private:
	ColourFactory m_colourFactory{};
	std::shared_ptr<IDeviceChannel> m_pDevChannel;
};