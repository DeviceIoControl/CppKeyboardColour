// Created by DeviceIoControl

#include "stdafx.h"
#include "WmiDeviceChannel.h"

#define CLEVO_WMI_OBJECT_NAME L"CLEVO_GET"
#define CLEVO_WMI_KB_METHOD_NAME L"SetKBLED"
#define CLEVO_WMI_INSTANCE_NAME L"CLEVO_GET.InstanceName='ACPI\\PNP0C14\\0_0'"

WmiDeviceChannel::WmiDeviceChannel(std::shared_ptr<IDeviceChannel> pDbgChannel /*= nullptr*/)
	: m_pDbgChannel(std::move(pDbgChannel))
{
	m_pClevoGetObject = m_wbemService.GetWbemClassObject(CLEVO_WMI_OBJECT_NAME);

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

	if (m_pDbgChannel)
	{
		std::ignore = m_pDbgChannel->SendCode(code);
	}

	const auto hr = m_pDataParameter->Put((BSTR)L"Data", NULL, &parameters, CIM_UINT32);
	std::ignore = m_wbemService.ExecuteMethod(CLEVO_WMI_INSTANCE_NAME, CLEVO_WMI_KB_METHOD_NAME, m_pDataParameter.Get());

	return SUCCEEDED(hr);
}