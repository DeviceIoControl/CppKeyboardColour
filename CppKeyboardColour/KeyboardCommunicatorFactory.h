// Created by DeviceIoControl

#pragma once

#include "stdafx.h"
#include "xstl.h"
#include "DeviceIds.h"
#include "IKeyboardCommunicator.h"

#include "WmiKBCommunicator.h"
#include "InsydeKBCommunicator.h"
#include "FakeKeyboardCommunicator.h"

#include "IDeviceIdTranslator.h"

class KeyboardCommunicatorFactory 
{
public:
	KeyboardCommunicatorFactory(std::unique_ptr<IDeviceIdTranslator> pDeviceIdTranslator)
		: m_pDeviceIdTranslator(std::move(pDeviceIdTranslator))
	{
	}

	IKeyboardCommunicatorPtr Create(uint32_t deviceId)
	{
		if (!m_pDeviceIdTranslator) 
		{
			return nullptr;
		}

		return m_kbComms[xstd::to_underlying(m_pDeviceIdTranslator->DeviceIdToKBCommunicatorType(deviceId))];
	}
	
	~KeyboardCommunicatorFactory() = default;

private:
	std::array<IKeyboardCommunicatorPtr, 4> m_kbComms{};
	std::unique_ptr<IDeviceIdTranslator> m_pDeviceIdTranslator{};
	
	void CreateKBCommunicators()
	{
		m_kbComms[xstd::to_underlying(KBCommunicatorType::None)] = nullptr;
		m_kbComms[xstd::to_underlying(KBCommunicatorType::Wmi)] = std::make_shared<WmiKBCommunicator>();
		m_kbComms[xstd::to_underlying(KBCommunicatorType::Insyde)] = std::make_shared<InsydeKBCommunicator>();
		m_kbComms[xstd::to_underlying(KBCommunicatorType::Fake)] = std::make_shared<FakeKeyboardCommunicator>();
	}
};