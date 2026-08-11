// Created by DeviceIoControl

#pragma once

#include "Zone.h"
#include "Colour.h"

enum class QueryType : uint16_t
{
	KeyboardType,
	DeviceChannelType,
	DeviceType
};

class IDevice
{
public:
	virtual ~IDevice() = default;
	virtual bool SetColour(Zone zone, const Colour& colour) = 0;
	virtual uint64_t Query(QueryType queryType) = 0;
	virtual bool SendCode(uint32_t code) = 0;
	virtual std::wstring GetName() const = 0;
};