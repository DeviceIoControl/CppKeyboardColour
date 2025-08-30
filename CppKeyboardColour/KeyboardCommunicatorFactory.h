// Created by DeviceIoControl

#pragma once

#include "stdafx.h"
#include "xstl.h"
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

		switch (m_pDeviceIdTranslator->DeviceIdToKBCommunicatorType(deviceId)) 
		{
		case KBCommunicatorType::None:
			return nullptr;

		case KBCommunicatorType::Fake:
			return std::make_shared<FakeKeyboardCommunicator>();

		case KBCommunicatorType::Wmi:
			return std::make_shared<WmiKBCommunicator>();

		case KBCommunicatorType::Insyde:
			return std::make_shared<InsydeKBCommunicator>();
		}
	}
	
	~KeyboardCommunicatorFactory() = default;

private:
	std::unique_ptr<IDeviceIdTranslator> m_pDeviceIdTranslator{};
};