#include "stdafx.h"
#include "ModelIdRetriever.h"
#include "WbemClassEnumerator.h"
#include "ModelIds.h"

#define CLEVO_DEVICE_OEM_ID 0x1558

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
		const auto devInstancePath = this->GetPnpDeviceId(object.Get());
		
		if (!this->IsPCIDeviceInstancePath(devInstancePath)) 
		{
			continue;
		}

		const auto subsystem = this->ExtractDeviceInstancePathSubsystem(devInstancePath);
		if (subsystem.empty()) 
		{
			continue;
		}

		const auto subSysId = this->ExtractSubsystemID(subsystem);
		if ((subSysId & 0xffff) != CLEVO_DEVICE_OEM_ID) 
		{
			continue;
		}

		return (subSysId & (0xffff << 16)) >> 16;
	}

	return 0;
}

uint32_t ModelIdRetriever::ExtractSubsystemID(const std::wstring& subsystem) 
{
	if (subsystem.empty() || subsystem.find(L'_') == std::wstring::npos)
	{
		return 0;
	}

	const auto subSysId = subsystem.substr(subsystem.find(L'_') + 1);
	return xstd::stoi(subSysId, 16).value_or(0);
}

bool ModelIdRetriever::IsPCIDeviceInstancePath(const std::wstring& devInstPath)
{
	return devInstPath.find_first_of(L"PCI\\") != std::wstring::npos;
}

std::wstring ModelIdRetriever::ExtractDeviceInstancePathSubsystem(const std::wstring& devInstPath) 
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

std::wstring ModelIdRetriever::GetPnpDeviceId(IWbemClassObject* pObject) 
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