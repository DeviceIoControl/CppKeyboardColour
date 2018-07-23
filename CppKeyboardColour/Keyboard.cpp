#include "stdafx.h"
#include "Keyboard.h"
#include <comdef.h>

#pragma comment(lib, "wbemuuid.lib")

Keyboard::Keyboard()
{
	CoInitializeEx(nullptr, COINIT::COINIT_APARTMENTTHREADED);
	CoInitializeSecurity(nullptr,
		-1,
		nullptr,
		nullptr,
		RPC_C_AUTHN_LEVEL_CONNECT,
		RPC_C_IMP_LEVEL_IMPERSONATE,
		nullptr,
		EOAC_NONE,
		nullptr);

	CoCreateInstance(CLSID_WbemLocator, nullptr, CLSCTX_INPROC_SERVER, IID_IWbemLocator, (void**)&m_WbemLocator);
	m_WbemLocator->ConnectServer((BSTR)L"ROOT\\WMI", nullptr, nullptr, nullptr, NULL, nullptr, nullptr, &m_WbemServices);
	
	m_WbemServices->GetObjectW((BSTR)L"CLEVO_GET", NULL, nullptr, &m_ClevoGetObj, nullptr);
	m_ClevoGetObj->GetMethod((BSTR)L"SetKBLED", NULL, &m_InOutParamaters[0], nullptr);
}

void Keyboard::SetColour(byte r, byte g, byte b, Zone zone)
{
	byte _paramData[4] = { g, r, b };

	VARIANT parameters = { 0 };
	parameters.vt = VT_I4;

	if (zone == Zone::ALL) {

		for (int i = 0; i < 3; ++i)
		{
			parameters.uintVal = (*(unsigned int*)&_paramData[0]) + ((unsigned int)(0xF0 + i) << 24);
			m_InOutParamaters[0]->Put((BSTR)L"Data", NULL, &parameters, CIM_UINT32);
			m_WbemServices->ExecMethod((BSTR)L"CLEVO_GET.InstanceName='ACPI\\PNP0C14\\0_0'",
				(BSTR)L"SetKBLED",
				NULL,
				nullptr,
				m_InOutParamaters[0],
				nullptr,
				nullptr);
		}
	} else {
		parameters.uintVal = (*(unsigned int*)&_paramData[0]) + ((unsigned int)(0xF0 + zone) << 24);
		m_InOutParamaters[0]->Put((BSTR)L"Data", NULL, &parameters, CIM_UINT32);
		m_WbemServices->ExecMethod((BSTR)L"CLEVO_GET.InstanceName='ACPI\\PNP0C14\\0_0'",
			(BSTR)L"SetKBLED",
			NULL,
			nullptr,
			m_InOutParamaters[0],
			nullptr,
			nullptr);
	}
}

void Keyboard::SysAnimation(SystemAnimation animation) 
{
	VARIANT parameters = { 0 };
	parameters.vt = VT_I4;
	parameters.uintVal = animation;
	m_InOutParamaters[0]->Put((BSTR)L"Data", NULL, &parameters, CIM_UINT32);
	m_WbemServices->ExecMethod((BSTR)L"CLEVO_GET.InstanceName='ACPI\\PNP0C14\\0_0'",
		(BSTR)L"SetKBLED",
		NULL,
		nullptr, 
		m_InOutParamaters[0], 
		nullptr, 
		nullptr);
}

Keyboard::~Keyboard()
{
	m_ClevoGetObj->Release();

	for (int i = 0; i < 2; ++i) {
		if (!m_InOutParamaters[i]) { continue; }
		m_InOutParamaters[i]->Release();
	}

	m_WbemServices->Release();
	m_WbemLocator->Release();
}
