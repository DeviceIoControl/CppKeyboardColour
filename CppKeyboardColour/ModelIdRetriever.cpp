// Created by DeviceIoControl

#include "stdafx.h"
#include "ModelIdRetriever.h"
#include "WbemClassEnumerator.h"
#include "ModelIds.h"

#define CLEVO_DEVICE_OEM_ID 0x1558

namespace 
{
	std::wstring GetWin32PnpEntityPNPDeviceIDProperty(IWbemClassObject* pObject) 
	{
		VARIANT var{};

		if (FAILED(pObject->Get(L"PNPDeviceID", 0, &var, nullptr, nullptr)))
		{
			return {};
		}

		if (var.vt != VT_BSTR)
		{
			return {};
		}

		std::wstring pnpDeviceId{ var.bstrVal };

		VariantClear(&var);

		return pnpDeviceId;
	}

	bool IsDeviceOnPCIBus(const std::wstring& devInstPath) 
	{
		return devInstPath.find(L"PCI\\") != std::wstring::npos;
	}

	std::wstring ExtractDeviceInstancePathSubsystem(const std::wstring& devInstPath) 
	{
		const auto subsysPosition = devInstPath.find(L"SUBSYS_");
		if (subsysPosition == std::wstring::npos)
		{
			return {};
		}

		const auto subsysEnd = devInstPath.find(L'&', subsysPosition);
		if (subsysEnd == std::wstring::npos)
		{
			return {};
		}

		return devInstPath.substr(subsysPosition, subsysEnd - subsysPosition);
	}

	uint32_t ExtractSubsystemID(const std::wstring& subsystem) 
	{
		if (subsystem.empty() || subsystem.find(L'_') == std::wstring::npos)
		{
			return 0;
		}

		const auto subSysId = subsystem.substr(subsystem.find(L'_') + 1);
		return xstd::stoi(subSysId, 16).value_or(0);
	}

} // namespace 

ModelIdRetriever::ModelIdRetriever(bool useDebugModel /*= false*/) 
	: m_useDbgModelId(useDebugModel)
{
}

uint32_t ModelIdRetriever::GetModelID()
{
	if (m_useDbgModelId)
	{
		return MODEL_ID_DEBUG;
	}

	WbemClassEnumerator enumerator = m_wbemService.GetWbemInstanceEnumerator(L"Win32_PnpEntity");
	
	while (const auto object = enumerator.Next())
	{
		const auto devInstancePath = GetWin32PnpEntityPNPDeviceIDProperty(object.Get());
		if (!IsDeviceOnPCIBus(devInstancePath))
		{
			continue;
		}

		const auto subsystem = ExtractDeviceInstancePathSubsystem(devInstancePath);
		if (subsystem.empty())
		{
			continue;
		}

		const auto subSysId = ExtractSubsystemID(subsystem);
		if ((subSysId & 0xffff) != CLEVO_DEVICE_OEM_ID)
		{
			continue;
		}

		return (subSysId & (0xffff << 16)) >> 16;
	}

	return 0;
}