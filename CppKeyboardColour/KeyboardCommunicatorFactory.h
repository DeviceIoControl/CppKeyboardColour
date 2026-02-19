// Created by DeviceIoControl
#pragma once

#include "IKeyboardCommunicator.h"
#include "IDeviceIdTranslator.h"

class KeyboardCommunicatorFactory 
{
public:
	KeyboardCommunicatorFactory(std::unique_ptr<IDeviceIdTranslator> pDeviceIdTranslator);

	IKeyboardCommunicatorPtr Create(uint32_t deviceId) const;

	~KeyboardCommunicatorFactory() = default;

private:
	std::unique_ptr<IDeviceIdTranslator> m_pDeviceIdTranslator{};
};