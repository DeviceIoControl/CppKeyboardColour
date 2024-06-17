#pragma once

#include "stdafx.h"
#include "IKeyboardCommunicator.h"

namespace Detail
{
	using T_WriteAppSettings = DWORD(__stdcall*)(DWORD dwPage, DWORD dwOffset, DWORD dwLength, const UINT8* pInBuffer);
}

class InsydeKBCommunicator 
	: public IKeyboardCommunicator 
{
public:
	InsydeKBCommunicator() 
	{
		m_hInsydeDHCU = LoadLibraryW(L"InsydeDCHU.dll");
		m_pfnWriteAppSettings = reinterpret_cast<Detail::T_WriteAppSettings>(GetProcAddress(m_hInsydeDHCU, "WriteAppSettings"));
	}

	bool SetKeyboardColour(Zone zone, const Colour& colour) override 
	{
		if (zone == Zone::ALL) 
		{
			const std::array<uint8_t, 3> colourBuffer
			{
				colour[INDEX_COLOUR_RED],
				colour[INDEX_COLOUR_GREEN],
				colour[INDEX_COLOUR_BLUE]
			};

			// Found in CLEVO Control Center v6.053
			std::ignore = m_pfnWriteAppSettings(2, 81, colourBuffer.size(), colourBuffer.data());

			return true;
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
			m_pfnWriteAppSettings = nullptr;
		}
	}

private:
	HMODULE m_hInsydeDHCU = nullptr;
	Detail::T_WriteAppSettings m_pfnWriteAppSettings = nullptr;
};