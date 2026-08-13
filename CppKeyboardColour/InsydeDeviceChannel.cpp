// Created by DeviceIoControl

#include "stdafx.h"
#include "InsydeDeviceChannel.h"
#include "ConsoleUtils.h"

#define INSYDE_DLL L"InsydeDCHU.dll"

InsydeDeviceChannel::InsydeDeviceChannel(std::shared_ptr<IDeviceChannel> pDbgChannel) 
	: m_pDbgChannel(std::move(pDbgChannel))
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

	if (m_pDbgChannel)
	{
		m_pDbgChannel->SendCode(code);
	}

	// Found in CLEVO Control Center v6.053
	uint8_t const mode = 8;
	uint32_t const colour = m_colourFactory.Convert(ColourFormat::B8R8G8, code & 0x00ffffff, ColourFormat::R8G8B8);

	m_pfnSetDCHU_Data(0x67, xstd::adjust_ptr<const uint8_t>(&code, 0), sizeof(code));
	m_pfnWriteAppSettings(2, 0x51, 3, xstd::adjust_ptr<const uint8_t>(&colour, 1));
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
