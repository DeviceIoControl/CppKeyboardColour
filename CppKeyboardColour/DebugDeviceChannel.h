// Created by DeviceIoControl

#pragma once
#include "IDeviceChannel.h"
#include "ColourFactory.h"
#include "KeyboardType.h"

class DebugDeviceChannel
	: public IDeviceChannel
{
public:
	DebugDeviceChannel(KeyboardType kbType);
	~DebugDeviceChannel() override = default;

	bool SendCode(uint32_t code) override;
	DeviceChannelType QueryType() const override;

private:
	KeyboardType m_kbType;
	ColourFactory m_colourFactory{};
};