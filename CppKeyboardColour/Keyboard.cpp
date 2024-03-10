// Created by DeviceIoControl

#include "stdafx.h"
#include "Keyboard.h"
#include "WbemService.h"

#define CLEVO_WMI_INSTANCE_NAME L"CLEVO_GET.InstanceName='ACPI\\PNP0C14\\0_0'"
#define GETPRODUCTDLL_PATH L"C:\\Program Files (x86)\\HotKey\\GetProductdll.dll"

Keyboard::Keyboard()
{
	m_pClevoGetObject = WMI::Get()->GetWbemClassObject(L"CLEVO_GET");

	IWbemClassObject* pDataParameter = nullptr;
	m_pClevoGetObject->GetMethod(L"SetKBLED", NULL, &pDataParameter, nullptr);

	m_pDataParameter.Reset(pDataParameter);

	m_uiDeviceId = GetDeviceID().value_or(~0);
}

void Keyboard::SetColour(uint8_t r, uint8_t g, uint8_t b, Zone zone)
{
	VARIANT parameters = { 0 };
	parameters.vt = VT_I4;

	if (zone == Zone::ALL)
	{
		for (int i = 0; i < 3; ++i)
		{
			const std::array<uint8_t, 4> parameterData{ g, r, b, 0xF0 + i };
			parameters.uintVal = *reinterpret_cast<const uint32_t*>(parameterData.data());

			m_pDataParameter->Put((BSTR)L"Data", NULL, &parameters, CIM_UINT32);

			std::ignore = WMI::Get()->ExecuteMethod(
				CLEVO_WMI_INSTANCE_NAME, L"SetKBLED", m_pDataParameter.Get()
			);
		}
	}
	else
	{
		const std::array<uint8_t, 4> parameterData{ g, r, b, 0xF0 + static_cast<uint16_t>(zone) };
		parameters.uintVal = *reinterpret_cast<const uint32_t*>(parameterData.data());

		m_pDataParameter->Put((BSTR)L"Data", NULL, &parameters, CIM_UINT32);

		std::ignore = WMI::Get()->ExecuteMethod(
			CLEVO_WMI_INSTANCE_NAME, L"SetKBLED", m_pDataParameter.Get()
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
		CLEVO_WMI_INSTANCE_NAME, L"SetKBLED", m_pDataParameter.Get()
	);
}

std::optional<uint32_t> Keyboard::DoGetDeviceID()
{
	//
	// Need to call CoInitialize to balance out COM initialization reference count
	// as the poorly programmed GetProductdll.dll attempts to change the threading-model 
	// of COM using CoInitializeEx and thus it's subsequent call to CoUninitialize raises 
	// an exception on the thread as COM was never initialised.
	//
	CoInitialize(nullptr);

	using T_GetProductID_PCI = uint32_t(__stdcall*)();
	HMODULE hGetProductDll = LoadLibraryW(GETPRODUCTDLL_PATH);
	
	if (!IS_HANDLE_VALID(hGetProductDll))
	{
		std::cout << "Failed to load GetProductdll.dll - Error code 0x" << (void*)GetLastError() << "\n";
		return std::nullopt;
	}

	if (auto const pfnGetProductID_PCI = (T_GetProductID_PCI)GetProcAddress(hGetProductDll, "GetProductID_PCI"))
	{
		auto const deviceId = pfnGetProductID_PCI();
		
		FreeLibrary(hGetProductDll);
		
		return deviceId;
	}

	std::cout << "Failed retrieve the Device ID - Error code 0x" << (void*)GetLastError() << "\n";

	FreeLibrary(hGetProductDll);

	return std::nullopt;
}

void Keyboard::DoAnimation(IAnimation& animation)
{
	for (size_t i = 0; i < animation.Size(); ++i)
	{
		if (auto frame = animation.GetFrame(i))
		{
			SetColour(frame->colour[2], frame->colour[1], frame->colour[0], frame->zone);
			Sleep(frame->ms_time);
		}
	}
}

void Keyboard::PlayAnimation(IAnimation& animation, bool bShouldLoop /*= true*/)
{
	if (animation.IsSupportedDevice(m_uiDeviceId))
	{
		do
		{
			this->DoAnimation(animation);

		} while (bShouldLoop);
	}
}
