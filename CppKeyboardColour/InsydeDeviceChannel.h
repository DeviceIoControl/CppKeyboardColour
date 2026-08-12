// Created by DeviceIoControl

#pragma once

#include "IDeviceChannel.h"
#include "ColourFactory.h"

namespace Detail
{
	using T_SetDCHU_Data = DWORD(__stdcall*)(DWORD command, const UINT8* buffer, DWORD length);
	using T_WriteAppSettings = DWORD(__stdcall*)(DWORD dwPage, DWORD dwOffset, DWORD dwLength, const UINT8* pInBuffer);
}

class InsydeDeviceChannel
	: public IDeviceChannel
{
public:
	InsydeDeviceChannel(std::shared_ptr<IDeviceChannel> pDbgChannel);
	~InsydeDeviceChannel() override;

	bool SendCode(uint32_t code) override;
	DeviceChannelType QueryType() const override;

private:
	ColourFactory m_colourFactory{};
	HMODULE m_hInsydeDHCU = nullptr;
	std::shared_ptr<IDeviceChannel> m_pDbgChannel{};
	Detail::T_SetDCHU_Data m_pfnSetDCHU_Data = nullptr;
	Detail::T_WriteAppSettings m_pfnWriteAppSettings = nullptr;

	HMODULE LoadInsydeDCHU_DLL() const;
};