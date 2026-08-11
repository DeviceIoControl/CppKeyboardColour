// Created by DeviceIoControl

#include "stdafx.h"
#include "Host.h"
#include "ColourFactory.h"

Host::Host(uint32_t modelId, const std::vector<std::shared_ptr<IDevice>>& devices)
	: m_modelId(modelId)
{
	for (auto const& pDevice : devices)
	{
		auto const deviceType = static_cast<DeviceMask>(pDevice->Query(QueryType::DeviceType));

		switch (deviceType)
		{
		case DeviceMask::Keyboard:
			m_pKeyboard = !m_pKeyboard ? pDevice : m_pKeyboard;
			break;

		case DeviceMask::Lightbar:
			m_pLightbar = !m_pLightbar ? pDevice : m_pLightbar;
			break;

		case DeviceMask::Logo:
			m_pLogo = !m_pLogo ? pDevice : m_pLogo;
			break;

		case DeviceMask::Unknown:
			continue;
		}
	}
}

DeviceMask Host::GetDevices() const
{
	return ((m_pKeyboard) ? DeviceMask::Keyboard : DeviceMask::Unknown)
		| ((m_pLightbar) ? DeviceMask::Lightbar : DeviceMask::Unknown)
		| ((m_pLogo) ? DeviceMask::Logo : DeviceMask::Unknown);
}

KeyboardType Host::GetKeyboardType() const
{
	return m_pKeyboard ? static_cast<KeyboardType>(m_pKeyboard->Query(QueryType::KeyboardType)) : KeyboardType::NONE;
}

uint32_t Host::GetModelID() const
{
	return m_modelId;
}

bool Host::SetKeyboardColour(Zone zone, const Colour& colour)
{
	return m_pKeyboard ? m_pKeyboard->SetColour(zone, colour) : false;
}

bool Host::SetLightbarColour(const Colour& colour)
{
	return m_pLightbar ? m_pLightbar->SetColour(Zone::ALL, colour) : false;
}

bool Host::SetLogoColour(const Colour& colour)
{
	return m_pLogo ? m_pLogo->SetColour(Zone::ALL, colour) : false;
}

bool Host::SetBacklightOn(DeviceMask devices)
{
	if (devices == DeviceMask::Unknown)
	{
		return false;
	}

	ColourFactory const colourFactory{};
	this->ApplyColour(devices, colourFactory.Create(0x00, 0x00, 0xFF));

	return true;
}

bool Host::SetBacklightOff(DeviceMask devices)
{
	if (devices == DeviceMask::Unknown)
	{
		return false;
	}

	Colour const offColour{};
	this->ApplyColour(devices, offColour);

	return true;
}

bool Host::SendDeviceCode(DeviceMask devices, uint32_t code)
{
	if (devices == DeviceMask::Unknown)
	{
		return false;
	}

	if (!!(devices & DeviceMask::Keyboard) && this->IsDeviceSendCodeCapable(m_pKeyboard))
	{
		m_pKeyboard->SendCode(code);
	}

	if (!!(devices & DeviceMask::Lightbar) && this->IsDeviceSendCodeCapable(m_pLightbar))
	{
		m_pLightbar->SendCode(code);
	}

	if (!!(devices & DeviceMask::Logo) && this->IsDeviceSendCodeCapable(m_pLogo))
	{
		m_pLogo->SendCode(code);
	}

	return true;
}

void Host::ApplyColour(DeviceMask devices, const Colour& colour)
{
	if (devices == DeviceMask::Unknown)
	{
		return;
	}

	if (m_pKeyboard && !!(devices & DeviceMask::Keyboard))
	{
		m_pKeyboard->SetColour(Zone::ALL, colour);
	}

	if (m_pLightbar && !!(devices & DeviceMask::Lightbar))
	{
		m_pLightbar->SetColour(Zone::ALL, colour);
	}

	if (m_pLogo && !!(devices & DeviceMask::Logo))
	{
		m_pLogo->SetColour(Zone::ALL, colour);
	}
}

bool Host::IsDeviceSendCodeCapable(std::shared_ptr<IDevice> pDevice) const 
{
	if (!pDevice) 
	{
		std::cout << "Cannot communicate with the requested device.\n";
		return false;
	} 

	if (static_cast<DeviceChannelType>(pDevice->Query(QueryType::DeviceChannelType)) != DeviceChannelType::Wmi) 
	{
		std::wcout << L"'" << pDevice->GetName() << L"' does not support this operation.\n";
		return false;
	}

	return true;
}