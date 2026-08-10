// Created by DeviceIoControl

#include "stdafx.h"
#include "FakeDeviceChannel.h"
#include "Zone.h"

bool FakeDeviceChannel::SendCode(uint32_t code)
{
	std::cout << "Code: 0x" << (void*)code << "\n";
	return true;
}

DeviceChannelType FakeDeviceChannel::QueryType() const 
{
	return DeviceChannelType::Fake;
}