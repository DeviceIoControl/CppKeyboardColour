// Created by DeviceIoControl

#pragma once

#include "IDeviceChannel.h"
#include "../ColourFactory.h"

class InsydeDeviceChannel
	: public IDeviceChannel
{
private:
	using T_SetDCHU_Data = DWORD(__stdcall*)(DWORD command, const UINT8* buffer, DWORD length);

public:
	InsydeDeviceChannel();
	~InsydeDeviceChannel() override;

	bool SendCode(uint32_t code) override;
	DeviceChannelType QueryType() const override;

private:
	ColourFactory m_colourFactory{};
	HMODULE m_hInsydeDHCU = nullptr;
	T_SetDCHU_Data m_pfnSetDCHU_Data = nullptr;
};