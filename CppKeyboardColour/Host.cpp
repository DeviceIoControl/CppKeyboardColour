// Created by DeviceIoControl

#include "stdafx.h"
#include "Host.h"
#include "ColourFactory.h"
#include "DeviceChannelType.h"

namespace 
{
	DeviceChannelType QueryDeviceChannelType(std::shared_ptr<IDevice> pDevice) 
	{
		return (pDevice) ? static_cast<DeviceChannelType>(pDevice->Query(QueryType::DeviceChannelType)) : DeviceChannelType::None;
	}

	DeviceMask QueryDeviceType(std::shared_ptr<IDevice> pDevice) 
	{
		return (pDevice) ? static_cast<DeviceMask>(pDevice->Query(QueryType::DeviceType)) : DeviceMask::Unknown;
	}

	bool TrySendDeviceCode(std::shared_ptr<IDevice> pDevice, uint32_t code) 
	{
		if (!pDevice)
		{
			std::cout << "Cannot communicate with the requested device.\n";
			return false;
		}

		return pDevice->SendCode(code);
	}

} // namespace

Host::Host(std::shared_ptr<ModelIdentifier> pModelId, const std::vector<std::shared_ptr<IDevice>>& devices)
	: m_modelId(pModelId->GetModelID()),
	m_modelName(pModelId->GetModelName()),
	m_devChannelType(pModelId->GetDeviceChannelType())
{
	for (const auto& pDevice : devices)
	{
		if (!pDevice)
		{
			continue;
		}

		switch (QueryDeviceType(pDevice))
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

std::wstring Host::GetModelName() const 
{
	return m_modelName;
}

DeviceChannelType Host::GetDeviceChannelType(DeviceMask device) const 
{
	switch (device)
	{
	case DeviceMask::Keyboard:
		return QueryDeviceChannelType(m_pKeyboard);

	case DeviceMask::Lightbar:
		return QueryDeviceChannelType(m_pLightbar);

	case DeviceMask::Logo:
		return QueryDeviceChannelType(m_pLogo);
	}

	return DeviceChannelType::None;
}

bool Host::SetColour(DeviceMask devices, Zone zone, const Colour& colour)
{
	if (devices == DeviceMask::Unknown)
	{
		return false;
	}

	if (m_pKeyboard && !!(devices & DeviceMask::Keyboard))
	{
		m_pKeyboard->SetColour(zone, colour);
	}

	if (m_pLightbar && !!(devices & DeviceMask::Lightbar))
	{
		m_pLightbar->SetColour(Zone::ALL, colour);
	}

	if (m_pLogo && !!(devices & DeviceMask::Logo))
	{
		m_pLogo->SetColour(Zone::ALL, colour);
	}

	return true;
}

bool Host::SetBacklightOn(DeviceMask devices)
{
	if (devices == DeviceMask::Unknown)
	{
		return false;
	}

	ColourFactory const colourFactory{};
	return this->SetColour(devices, Zone::ALL, colourFactory.Create(ColourValue::BLUE));
}

bool Host::SetBacklightOff(DeviceMask devices)
{
	if (devices == DeviceMask::Unknown)
	{
		return false;
	}

	Colour const offColour{};
	return this->SetColour(devices, Zone::ALL, offColour);
}

bool Host::SendDeviceCode(DeviceMask devices, uint32_t code)
{
	if (devices == DeviceMask::Unknown)
	{
		return false;
	}

	if (!!(devices & DeviceMask::Keyboard))
	{
		TrySendDeviceCode(m_pKeyboard, code);
	}

	if (!!(devices & DeviceMask::Lightbar))
	{
		TrySendDeviceCode(m_pLightbar, code);
	}

	if (!!(devices & DeviceMask::Logo))
	{
		TrySendDeviceCode(m_pLogo, code);
	}

	return true;
}
