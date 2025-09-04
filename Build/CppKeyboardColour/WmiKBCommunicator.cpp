// Created by DeviceIoControl

#include "stdafx.h"
#include "WmiKBCommunicator.h"
#include "WbemService.h"

#define CLEVO_WMI_OBJECT_NAME L"CLEVO_GET"
#define CLEVO_WMI_KB_FUNCTION_NAME L"SetKBLED"
#define CLEVO_WMI_INSTANCE_NAME L"CLEVO_GET.InstanceName='ACPI\\PNP0C14\\0_0'"

WmiKBCommunicator::WmiKBCommunicator()
{
	m_pClevoGetObject = WMI::Get()->GetWbemClassObject(CLEVO_WMI_OBJECT_NAME);

	IWbemClassObject* pDataParameter = nullptr;
	m_pClevoGetObject->GetMethod(CLEVO_WMI_KB_FUNCTION_NAME, NULL, &pDataParameter, nullptr);

	m_pDataParameter.Reset(pDataParameter);
}

bool WmiKBCommunicator::SetKBColour(Zone zone, const Colour& colour)
{
	if (zone == Zone::ALL)
	{
		for (int i = 0; i < 3; ++i)
		{
			const std::array<uint8_t, 4> parameterData
			{
				colour[INDEX_COLOUR_GREEN],
				colour[INDEX_COLOUR_RED],
				colour[INDEX_COLOUR_BLUE],
				0xF0 + i
			};

			this->SendKBCode(*reinterpret_cast<const uint32_t*>(parameterData.data()));
		}

		return true;
	}
	else
	{
		const std::array<uint8_t, 4> parameterData
		{
			colour[INDEX_COLOUR_GREEN],
			colour[INDEX_COLOUR_RED],
			colour[INDEX_COLOUR_BLUE],
			0xF0 + static_cast<uint16_t>(zone)
		};

		return this->SendKBCode(*reinterpret_cast<const uint32_t*>(parameterData.data()));
	}

	return false;
}

bool WmiKBCommunicator::SendKBCode(uint32_t code)
{
	VARIANT parameters = { 0 };
	parameters.vt = VT_I4;
	parameters.uintVal = code;

	const auto hr = m_pDataParameter->Put((BSTR)L"Data", NULL, &parameters, CIM_UINT32);
	std::ignore = WMI::Get()->ExecuteMethod(CLEVO_WMI_INSTANCE_NAME, CLEVO_WMI_KB_FUNCTION_NAME, m_pDataParameter.Get());

	return SUCCEEDED(hr);
}