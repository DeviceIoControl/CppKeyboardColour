// Created by DeviceIoControl

#pragma once

#include "../Colour.h"
#include "../Common/Zone.h"
#include "../ColourFactory.h"
#include "../Devices/IDevice.h"
#include "../Channels/IDeviceChannel.h"

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