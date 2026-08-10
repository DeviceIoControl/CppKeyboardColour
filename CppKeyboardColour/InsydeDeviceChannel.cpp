// Created by DeviceIoControl

#include "stdafx.h"
#include "InsydeDeviceChannel.h"
#include "ConsoleUtils.h"

#define INSYDE_DLL L"InsydeDCHU.dll"

InsydeDeviceChannel::InsydeDeviceChannel()
{
	m_hInsydeDHCU = LoadInsydeDCHU_DLL();

	m_pfnSetDCHU_Data = reinterpret_cast<Detail::T_SetDCHU_Data>(GetProcAddress(m_hInsydeDHCU, "SetDCHU_Data"));
	m_pfnWriteAppSettings = reinterpret_cast<Detail::T_WriteAppSettings>(GetProcAddress(m_hInsydeDHCU, "WriteAppSettings"));
}

bool InsydeDeviceChannel::SendCode(uint32_t code)
{
	if (!m_pfnSetDCHU_Data || !m_pfnWriteAppSettings)
	{
		return false;
	}

	// Found in CLEVO Control Center v6.053
	uint8_t const mode = 8;

	const std::array<uint8_t, 4> dchuData{
		(code & 0x0000ff00) >> 8,	// colour[INDEX_COLOUR_GREEN]
		(code & 0x00ff0000) >> 16,	// colour[INDEX_COLOUR_RED]
		(code & 0x000000ff),		// colour[INDEX_COLOUR_BLUE]
		(code & 0xff000000) >> 24	// keyboard region
	};

	m_pfnSetDCHU_Data(0x67, dchuData.data(), sizeof(dchuData));
	m_pfnWriteAppSettings(2, 0x51, 3, reinterpret_cast<uint8_t*>(code) + 1);
	m_pfnWriteAppSettings(2, 0x20, 1, &mode);

	return true;
}

DeviceChannelType InsydeDeviceChannel::QueryType() const 
{
	return DeviceChannelType::Insyde;
}

InsydeDeviceChannel::~InsydeDeviceChannel()
{
	if (IS_HANDLE_VALID(m_hInsydeDHCU))
	{
		FreeLibrary(m_hInsydeDHCU);
		m_pfnSetDCHU_Data = nullptr;
		m_pfnWriteAppSettings = nullptr;
	}
}

HMODULE InsydeDeviceChannel::LoadInsydeDCHU_DLL() const
{
	auto const hModule = LoadLibraryW(INSYDE_DLL);

	if (!hModule || hModule == INVALID_HANDLE_VALUE)
	{
		std::wcout << L"Cannot load " << INSYDE_DLL << L". Please ensure the DLL is within the same directory!\n";
		WaitForEnterIfNeeded();
		std::exit(STATUS_DLL_NOT_FOUND);
	}

	return hModule;
}
