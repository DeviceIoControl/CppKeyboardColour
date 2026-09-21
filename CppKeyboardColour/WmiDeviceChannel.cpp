// Created by DeviceIoControl

#include "stdafx.h"
#include "WmiDeviceChannel.h"
#include "ConsoleUtils.h"
#include "FileUtils.h"
#include "RegUtils.h"

#define CLEVO_WMI_OBJECT_NAME L"CLEVO_GET"
#define CLEVO_WMI_KB_METHOD_NAME L"SetKBLED"
#define CLEVO_WMI_INSTANCE_NAME L"CLEVO_GET.InstanceName='ACPI\\PNP0C14\\0_0'"

#define CLEVO_MOF_PATH L"C:\\Windows\\SysWOW64\\clevomof.dll"
#define CLEVO_MOF_REGKEY L"SYSTEM\\CurrentControlSet\\Services\\WmiAcpi"
#define CLEVO_MOF_REGVALUE L"MofImagePath"

namespace
{
	std::wstring GetClevoMofRegisteredPath()
	{
		return Registry::GetRegSzValue(HKEY_LOCAL_MACHINE, CLEVO_MOF_REGKEY, CLEVO_MOF_REGVALUE);
	}

	bool VerifyClevoMofRegisteredPath(const std::wstring& path) 
	{
		if (path.empty()) 
		{
			return false;
		}

		const auto _path = xstd::to_lower_case(path);

		if (_path.find(L"syswow64\\clevomof.dll") == std::wstring::npos) 
		{
			return false;
		}

		return true;
	}

	bool VerifyClevoMofRegistration()
	{
		const auto clevoMofRegisteredPath = GetClevoMofRegisteredPath();
		
		if (clevoMofRegisteredPath.empty())
		{
			PromptUserOnError(L"Cannot load clevomof.dll.\nPlease ensure the DLL is registered correctly.");
			return false;
		}
		
		if (!VerifyClevoMofRegisteredPath(clevoMofRegisteredPath)) 
		{
			PromptUserOnError(L"Cannot load clevomof.dll.\n");
			return false;
		}

		if (!File::Exists(CLEVO_MOF_PATH))
		{
			const std::wstring errMsg(L"Cannot load clevomof.dll.\nPlease ensure the DLL is at: " + clevoMofRegisteredPath);
			PromptUserOnError(errMsg);
			return false;
		}

		return true;
	}

} // namespace 

WmiDeviceChannel::WmiDeviceChannel()
{	
	if (!VerifyClevoMofRegistration())
	{
		std::exit(STATUS_DLL_NOT_FOUND);
	}

	m_pClevoGetObject = m_wbemService.GetWbemClassObject(CLEVO_WMI_OBJECT_NAME);

	if (!m_pClevoGetObject)
	{
		PromptUserOnError(L"CLEVOMOF.dll is registered - Failed to access code.\nPlease restart your system and try again.");
		std::exit(ERROR_INVALID_OPERATION);
	}

	IWbemClassObject* pDataParameter = nullptr;
	m_pClevoGetObject->GetMethod(CLEVO_WMI_KB_METHOD_NAME, NULL, &pDataParameter, nullptr);
	m_pDataParameter.Reset(pDataParameter);
}

DeviceChannelType WmiDeviceChannel::QueryType() const
{
	return DeviceChannelType::Wmi;
}

bool WmiDeviceChannel::SendCode(uint32_t code)
{
	VARIANT parameters = { 0 };
	parameters.vt = VT_I4;
	parameters.uintVal = code;

	const auto hr = m_pDataParameter->Put((BSTR)L"Data", NULL, &parameters, CIM_UINT32);
	std::ignore = m_wbemService.ExecuteMethod(CLEVO_WMI_INSTANCE_NAME, CLEVO_WMI_KB_METHOD_NAME, m_pDataParameter.Get());

	return SUCCEEDED(hr);
}