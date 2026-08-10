// Created by DeviceIoControl

#pragma once

#include "stdafx.h"
#include "DeviceChannelType.h"

class IDeviceChannel
{
public:
	virtual ~IDeviceChannel() = default;
	virtual bool SendCode(uint32_t code) = 0;
	virtual DeviceChannelType QueryType() const = 0;
};