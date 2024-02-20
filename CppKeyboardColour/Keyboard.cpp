// Created by DeviceIoControl

#include "stdafx.h"
#include "Keyboard.h"
#include "WbemService.h"

Keyboard::Keyboard()
{
	m_pClevoGetObject = WMI::Get()->GetWbemClassObject(L"CLEVO_GET");

	IWbemClassObject* pDataParameter = nullptr;
	m_pClevoGetObject->GetMethod(L"SetKBLED", NULL, &pDataParameter, nullptr);

	m_pDataParameter.Reset(pDataParameter);
}

void Keyboard::SetColour(uint8_t r, uint8_t g, uint8_t b, Zone zone)
{
	VARIANT parameters = { 0 };
	parameters.vt = VT_I4;
	
	if (zone == Zone::ALL) 
	{
		for (int i = 0; i < 3; ++i) 
		{
			std::array<uint8_t, 4> parameterData{ g, r, b, 0xF0 + i };
			parameters.uintVal = *reinterpret_cast<uint32_t*>(parameterData.data());

			m_pDataParameter->Put((BSTR)L"Data", NULL, &parameters, CIM_UINT32);
			
			std::ignore = WMI::Get()->ExecuteMethod(
				L"CLEVO_GET.InstanceName='ACPI\\PNP0C14\\0_0'", L"SetKBLED", m_pDataParameter.Get()
			);
		}
	} 
	else 
	{	
		std::array<uint8_t, 4> parameterData{ g, r, b, 0xF0 + static_cast<uint16_t>(zone) };
		parameters.uintVal = *reinterpret_cast<uint32_t*>(parameterData.data());
		
		m_pDataParameter->Put((BSTR)L"Data", NULL, &parameters, CIM_UINT32);
		
		std::ignore = WMI::Get()->ExecuteMethod(
			L"CLEVO_GET.InstanceName='ACPI\\PNP0C14\\0_0'", L"SetKBLED", m_pDataParameter.Get()
		);
	}
}

void Keyboard::SysAnimation(SystemAnimation animation) 
{
	switch (animation)
	{
	case SystemAnimation::KB_MODE_OFF:
		return this->SetColour(0x00, 0x00, 0x00, Zone::ALL);

	case SystemAnimation::KB_MODE_STANDARD:
		return this->SetColour(0x00, 0x00, 0xFF, Zone::ALL);
	}

	VARIANT parameters{};
	parameters.vt = VT_I4;
	parameters.uintVal = static_cast<uint32_t>(animation);

	m_pDataParameter->Put((BSTR)L"Data", NULL, &parameters, CIM_UINT32);
	
	std::ignore = WMI::Get()->ExecuteMethod(
		L"CLEVO_GET.InstanceName='ACPI\\PNP0C14\\0_0'", L"SetKBLED", m_pDataParameter.Get()
	);
}

void Keyboard::PlayAnimation(Animation& animation, bool bShouldLoop /*= true*/) 
{
	while (bShouldLoop)
	{
		for (size_t i = 0; i < animation.size(); ++i)
		{
			if (auto frame = animation.getFrame(i))
			{
				this->SetColour(frame->colour[2], frame->colour[1], frame->colour[0], frame->zone);
				Sleep(frame->ms_time);
			}
		}
	}
}
