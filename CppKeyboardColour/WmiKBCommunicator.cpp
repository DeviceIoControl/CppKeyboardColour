// Created by DeviceIoControl

#include "stdafx.h"
#include "WmiKBCommunicator.h"

#define CLEVO_WMI_OBJECT_NAME L"CLEVO_GET"
#define CLEVO_WMI_KB_FUNCTION_NAME L"SetKBLED"
#define CLEVO_WMI_INSTANCE_NAME L"CLEVO_GET.InstanceName='ACPI\\PNP0C14\\0_0'"

WmiKBCommunicator::WmiKBCommunicator(KeyboardType kbType)
	: m_kbType(kbType)
{
	m_pClevoGetObject = m_wbemService.GetWbemClassObject(CLEVO_WMI_OBJECT_NAME);

	IWbemClassObject* pDataParameter = nullptr;
	m_pClevoGetObject->GetMethod(CLEVO_WMI_KB_FUNCTION_NAME, NULL, &pDataParameter, nullptr);

	m_pDataParameter.Reset(pDataParameter);
}

bool WmiKBCommunicator::SetKBColour(Zone zone, const Colour& colour)
{
	// Cannot set lightbar colour from here, that must be done in a seperate method.
	if ((zone > Zone::ALL) || (zone == Zone::LIGHTBAR))
	{
		return false;
	}

	// Callers must always address "ALL" zones on a single-zone keyboard.
	if (m_kbType == KeyboardType::SINGLE_ZONE && zone != Zone::ALL)
	{
		return false;
	}

	return (zone != Zone::ALL) ? this->SetKBZoneColour(zone, colour) : this->SetFullKBColour(colour);
}

bool WmiKBCommunicator::SetKBZoneColour(Zone zone, const Colour& colour)
{
	auto const kbCode = xstd::to_underlying(zone) << 24ul | m_colourFactory.Create(colour);
	return (zone != Zone::LIGHTBAR) ? this->SendKBCode(kbCode) : false;
}

bool WmiKBCommunicator::SetLightbarColour(const Colour& colour)
{
	auto const kbCode = xstd::to_underlying(Zone::LIGHTBAR) << 24ul | m_colourFactory.Create(colour);
	return this->SendKBCode(kbCode);
}

bool WmiKBCommunicator::SetFullKBColour(const Colour& colour)
{
	if (m_kbType == KeyboardType::SINGLE_ZONE) 
	{
		// Left zone addresses the entire keyboard (Single-Zone).
		return this->SetKBZoneColour(Zone::LEFT, colour);
	}

	for (auto const currentZone : { Zone::LEFT, Zone::MID, Zone::RIGHT })
	{
		// Not checking for success here as we don't gain anything by bailing out on failed calls.
		std::ignore = this->SetKBZoneColour(currentZone, colour);
	}

	return true;
}

bool WmiKBCommunicator::SendKBCode(uint32_t code)
{
	VARIANT parameters = { 0 };
	parameters.vt = VT_I4;
	parameters.uintVal = code;

	const auto hr = m_pDataParameter->Put((BSTR)L"Data", NULL, &parameters, CIM_UINT32);
	std::ignore = m_wbemService.ExecuteMethod(CLEVO_WMI_INSTANCE_NAME, CLEVO_WMI_KB_FUNCTION_NAME, m_pDataParameter.Get());

	return SUCCEEDED(hr);
}