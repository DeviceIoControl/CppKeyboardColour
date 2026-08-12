// Created by DeviceIoControl

#pragma once
#include "IDeviceChannel.h"
#include "ColourFactory.h"

class FakeDeviceChannel
	: public IDeviceChannel
{
public:
	FakeDeviceChannel() = default;
	~FakeDeviceChannel() override = default;

	bool SendCode(uint32_t code) override;
	DeviceChannelType QueryType() const override;

private:
	ColourFactory m_colourFactory{};
};