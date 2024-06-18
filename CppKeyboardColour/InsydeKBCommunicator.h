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
		m_pfnKBProc = reinterpret_cast<Detail::T_SetDCHU_Data>(GetProcAddress(m_hInsydeDHCU, "SetDCHU_Data"));
	}

	bool SetKeyboardColour(Zone zone, const Colour& colour) override
	{
		// Found in CLEVO Control Center v6.053
		for (int i = 1; i < 4; ++i)
		{
			const std::array<uint8_t, 4> parameterData
			{
				colour[INDEX_COLOUR_GREEN],
				colour[INDEX_COLOUR_RED],
				colour[INDEX_COLOUR_BLUE],
				0xF0 + i
			};

			m_pfnKBProc(103, parameterData.data(), parameterData.size());
		}

		return false;
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
			m_pfnKBProc = nullptr;
		}
	}

private:
	HMODULE m_hInsydeDHCU = nullptr;
	Detail::T_SetDCHU_Data m_pfnKBProc = nullptr;
};