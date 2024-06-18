// Created by DeviceIoControl

#pragma once

#include "stdafx.h"
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
	InsydeKBCommunicator()
	{
		m_hInsydeDHCU = LoadLibraryW(L"InsydeDCHU.dll");
		m_pfnSetDCHU_Data = reinterpret_cast<Detail::T_SetDCHU_Data>(GetProcAddress(m_hInsydeDHCU, "SetDCHU_Data"));
		m_pfnWriteAppSettings = reinterpret_cast<Detail::T_WriteAppSettings>(GetProcAddress(m_hInsydeDHCU, "WriteAppSettings"));
	}

	bool SetKeyboardColour(Zone zone, const Colour& colour) override
	{
		if (zone != Zone::ALL) 
		{
			return false;
		}

		// Found in CLEVO Control Center v6.053
		const uint8_t mode = 8;

		const std::array<uint8_t, 4> dchuData {
			colour[INDEX_COLOUR_GREEN],
			colour[INDEX_COLOUR_RED],
			colour[INDEX_COLOUR_BLUE],
			0xF0
		};

		m_pfnSetDCHU_Data(103, dchuData.data(), dchuData.size());
		m_pfnWriteAppSettings(2, 81, colour.size(), colour.data());
		m_pfnWriteAppSettings(2, 32, 1, &mode);

		return true;
	}

	// Unsupported for now.
	bool SendKeyboardData(uint32_t data) override
	{
		return false;
	}

	~InsydeKBCommunicator() override
	{
		if (IS_HANDLE_VALID(m_hInsydeDHCU))
		{
			FreeLibrary(m_hInsydeDHCU);
			m_pfnSetDCHU_Data = nullptr;
			m_pfnWriteAppSettings = nullptr;
		}
	}

private:
	HMODULE m_hInsydeDHCU = nullptr;
	Detail::T_SetDCHU_Data m_pfnSetDCHU_Data = nullptr;
	Detail::T_WriteAppSettings m_pfnWriteAppSettings = nullptr;
};