// Created by DeviceIoControl

#include "stdafx.h"
#include "KeyboardCommunicatorFactory.h"

#include "WmiKBCommunicator.h"
#include "InsydeKBCommunicator.h"
#include "FakeKeyboardCommunicator.h"

KeyboardCommunicatorFactory::KeyboardCommunicatorFactory(std::unique_ptr<IDeviceIdTranslator> pDeviceIdTranslator)
	: m_pDeviceIdTranslator(std::move(pDeviceIdTranslator))
{
}

IKeyboardCommunicatorPtr KeyboardCommunicatorFactory::Create(uint32_t deviceId)
{
	if (!m_pDeviceIdTranslator)
	{
		return nullptr;
	}

	switch (m_pDeviceIdTranslator->DeviceIdToKBCommunicatorType(deviceId))
	{
	case KBCommunicatorType::Fake:
		return std::make_shared<FakeKeyboardCommunicator>();

	case KBCommunicatorType::Wmi:
		return std::make_shared<WmiKBCommunicator>();

	case KBCommunicatorType::Insyde:
		return std::make_shared<InsydeKBCommunicator>();
	}

	return nullptr;
}
