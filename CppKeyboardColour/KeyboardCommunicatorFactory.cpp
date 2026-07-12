// Created by DeviceIoControl

#include "stdafx.h"
#include "KeyboardCommunicatorFactory.h"

#include "WmiKBCommunicator.h"
#include "InsydeKBCommunicator.h"
#include "FakeKeyboardCommunicator.h"

KeyboardCommunicatorFactory::KeyboardCommunicatorFactory(std::shared_ptr<IKeyboardDevice> pKBDevice)
	: m_pKBDevice(std::move(pKBDevice))
{
}

std::shared_ptr<IKeyboardCommunicator> KeyboardCommunicatorFactory::Create() const
{
	if (!m_pKBDevice)
	{
		return nullptr;
	}

	auto const kbType = m_pKBDevice->GetKeyboardType();

	switch (m_pKBDevice->GetKBCommunicatorType())
	{
	case KBCommunicatorType::Fake:
		return std::make_shared<FakeKeyboardCommunicator>();

	case KBCommunicatorType::Wmi:
		return std::make_shared<WmiKBCommunicator>(kbType);

	case KBCommunicatorType::Insyde:
		return std::make_shared<InsydeKBCommunicator>();
	}

	return nullptr;
}
