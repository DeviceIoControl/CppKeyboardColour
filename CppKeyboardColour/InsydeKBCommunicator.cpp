// Created by DeviceIoControl

#include "stdafx.h"
#include "InsydeKBCommunicator.h"

#define INSYDE_DLL L"InsydeDCHU.dll"

InsydeKBCommunicator::InsydeKBCommunicator()
{
	m_hInsydeDHCU = LoadInsydeDCHU_DLL();

	m_pfnSetDCHU_Data = reinterpret_cast<Detail::T_SetDCHU_Data>(GetProcAddress(m_hInsydeDHCU, "SetDCHU_Data"));
	m_pfnWriteAppSettings = reinterpret_cast<Detail::T_WriteAppSettings>(GetProcAddress(m_hInsydeDHCU, "WriteAppSettings"));
}

bool InsydeKBCommunicator::SetKeyboardColour(Zone zone, const Colour& colour) 
{
	if (zone != Zone::ALL)
	{
		return false;
	}

	// Found in CLEVO Control Center v6.053
	const uint8_t mode = 8;

	const std::array<uint8_t, 4> dchuData{
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
bool InsydeKBCommunicator::SendKeyboardData(uint32_t data)
{
	return false;
}

InsydeKBCommunicator::~InsydeKBCommunicator()
{
	if (IS_HANDLE_VALID(m_hInsydeDHCU))
	{
		FreeLibrary(m_hInsydeDHCU);
		m_pfnSetDCHU_Data = nullptr;
		m_pfnWriteAppSettings = nullptr;
	}
}

HMODULE InsydeKBCommunicator::LoadInsydeDCHU_DLL() const
{
	auto const hModule = LoadLibraryW(INSYDE_DLL);

	if (!hModule || hModule == INVALID_HANDLE_VALUE)
	{
		std::wcout << L"Cannot load " << INSYDE_DLL << L". Please ensure the DLL is within the same directory!\n";
		std::exit(STATUS_DLL_NOT_FOUND);
	}

	return hModule;
}
