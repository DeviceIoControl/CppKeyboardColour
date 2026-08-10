// Created by DeviceIoControl

#pragma once

#include "DeviceMask.h"
#include "KeyboardType.h"
#include "Zone.h"
#include "Colour.h"

class IHost 
{
public:
	virtual ~IHost() = default;

	virtual DeviceMask GetDevices() const = 0;
	virtual KeyboardType GetKeyboardType() const = 0;
	virtual uint32_t GetModelID() const = 0;
	virtual bool SetKeyboardColour(Zone zone, const Colour& colour) = 0;
	virtual bool SetLightbarColour(const Colour& colour) = 0;
	virtual bool SetLogoColour(const Colour& colour) = 0;
	virtual bool SetBacklightOn(DeviceMask devices) = 0;
	virtual bool SetBacklightOff(DeviceMask devices) = 0;
	virtual bool SendDeviceCode(DeviceMask devices, uint32_t code) = 0;
};