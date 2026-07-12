// Created by DeviceIoControl

#include "stdafx.h"
#include "InsydeKBCommunicator.h"
#include "ConsoleUtils.h"

#define INSYDE_DLL L"InsydeDCHU.dll"

InsydeKBCommunicator::InsydeKBCommunicator()
{
	m_hInsydeDHCU = LoadInsydeDCHU_DLL();

	m_pfnSetDCHU_Data = reinterpret_cast<Detail::T_SetDCHU_Data>(GetProcAddress(m_hInsydeDHCU, "SetDCHU_Data"));
	m_pfnWriteAppSettings = reinterpret_cast<Detail::T_WriteAppSettings>(GetProcAddress(m_hInsydeDHCU, "WriteAppSettings"));
}

bool InsydeKBCommunicator::SetKBColour(Zone zone, const Colour& colour) 
{
	if (zone != Zone::ALL)
	{
		return false;
	}

	// Found in CLEVO Control Center v6.053
	uint8_t const mode = 8;
	auto const dchuData = xstd::to_underlying(Zone::LEFT) << 24ul | m_colourFactory.Create(colour);

	m_pfnSetDCHU_Data(0x67, reinterpret_cast<const uint8_t*>(&dchuData), sizeof(dchuData));
	m_pfnWriteAppSettings(2, 0x51, colour.size(), colour.data());
	m_pfnWriteAppSettings(2, 0x20, 1, &mode);

	return true;
}

// Unsupported for now.
bool InsydeKBCommunicator::SendKBCode(uint32_t /* code */)
{
	std::cout << "This system does not support this operation.\n";
	return false;
}

// Unsupported.
bool InsydeKBCommunicator::SetLightbarColour(const Colour& /*colour*/) 
{
	std::cout << "This system does not support this operation.\n";
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
		WaitForEnterIfNeeded();
		std::exit(STATUS_DLL_NOT_FOUND);
	}

	return hModule;
}
