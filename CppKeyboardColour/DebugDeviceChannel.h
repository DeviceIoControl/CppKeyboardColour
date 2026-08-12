// Created by DeviceIoControl

#pragma once
#include "IDeviceChannel.h"
#include "ColourFactory.h"

class DebugDeviceChannel
	: public IDeviceChannel
{
public:
	DebugDeviceChannel() = default;
	~DebugDeviceChannel() override = default;

	bool SendCode(uint32_t code) override;
	DeviceChannelType QueryType() const override;

private:
	ColourFactory m_colourFactory{};
};