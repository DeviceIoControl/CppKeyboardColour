// Created by DeviceIoControl

#pragma once

#include "IDevice.h"
#include "Colour.h"
#include "IDeviceChannel.h"
#include "ColourFactory.h"
#include "KeyboardType.h"

class KeyboardDevice
	: public IDevice
{
public:
	KeyboardDevice(KeyboardType kbType, std::shared_ptr<IDeviceChannel> pDeviceChannel);
	~KeyboardDevice() override = default;

	bool SetColour(Zone zone, const Colour& colour) override;
	uint64_t Query(QueryType queryType) override;
	bool SendCode(uint32_t code) override;
	std::wstring GetName() const override;
	
private:
	KeyboardType m_kbType;
	ColourFactory m_colourFactory;
	std::shared_ptr<IDeviceChannel> m_pDevChannel;

	bool SetKBZoneColour(Zone zone, const Colour& colour);
	bool SetFullKBColour(const Colour& colour);
};
