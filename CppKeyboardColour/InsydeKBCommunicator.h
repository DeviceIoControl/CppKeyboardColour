// Created by DeviceIoControl

#pragma once

#include "IKeyboardCommunicator.h"

namespace Detail
{
	using T_SetDCHU_Data = DWORD(__stdcall*)(DWORD command, const UINT8* buffer, DWORD length);
	using T_WriteAppSettings = DWORD(__stdcall*)(DWORD dwPage, DWORD dwOffset, DWORD dwLength, const UINT8* pInBuffer);
}

class InsydeKBCommunicator
	: public IKeyboardCommunicator
{
public:
	InsydeKBCommunicator();

	bool SetKeyboardColour(Zone zone, const Colour& colour) override;

	// Unsupported for now.
	bool SendKeyboardData(uint32_t data) override;

	~InsydeKBCommunicator() override;

private:
	HMODULE m_hInsydeDHCU = nullptr;
	Detail::T_SetDCHU_Data m_pfnSetDCHU_Data = nullptr;
	Detail::T_WriteAppSettings m_pfnWriteAppSettings = nullptr;

	HMODULE LoadInsydeDCHU_DLL() const;
};