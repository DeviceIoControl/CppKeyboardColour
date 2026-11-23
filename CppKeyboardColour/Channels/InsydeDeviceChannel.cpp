// Created by DeviceIoControl

#include "stdafx.h"
#include "InsydeDeviceChannel.h"
#include "../Console/Logger.h"

#define INSYDE_DLL L"InsydeDCHU.dll"


namespace 
{
	HMODULE LoadInsydeDCHU_DLL() 
	{
		const auto hModule = LoadLibraryW(INSYDE_DLL);

		if (!hModule || hModule == INVALID_HANDLE_VALUE)
		{
			KB_SET_FATAL_ERROR(STATUS_DLL_NOT_FOUND);
			KB_FATAL(L"Cannot load %s. Please ensure the DLL is within the same directory!", INSYDE_DLL);
		}

		return hModule;
	}
} // namespace

InsydeDeviceChannel::InsydeDeviceChannel()
{
	m_hInsydeDHCU = LoadInsydeDCHU_DLL();

	m_pfnSetDCHU_Data = reinterpret_cast<T_SetDCHU_Data>(GetProcAddress(m_hInsydeDHCU, "SetDCHU_Data"));
}

bool InsydeDeviceChannel::SendCode(uint32_t code)
{
	if (!m_pfnSetDCHU_Data)
	{
		return false;
	}

	// Found in CLEVO Control Center v6.053
	m_pfnSetDCHU_Data(0x67, xstd::adjust_ptr<const uint8_t>(&code, 0), sizeof(code));
	
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
	}
}