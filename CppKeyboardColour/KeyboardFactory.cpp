// Created by DeviceIoControl

#include "stdafx.h"
#include "KeyboardFactory.h"
#include "Keyboard.h"
#include "DeviceIdTranslator.h"
#include "KeyboardCommunicatorFactory.h"

std::unique_ptr<IKeyboard> KeyboardFactory::Create() const 
{
	const auto deviceId = m_deviceIdRetriever.GetDeviceID();

	std::cout << "Detected Device ID: 0x" << (void*)deviceId << "\n";

	auto ptrDevIdTranslator = std::make_unique<DeviceIdTranslator>();
	const auto kbType = ptrDevIdTranslator->TranslateToKBType(deviceId);

	if (kbType == KeyboardType::NONE)
	{
		return nullptr;
	}

	KeyboardCommunicatorFactory kbCommFactory(std::move(ptrDevIdTranslator));
	auto ptrKbComms = kbCommFactory.Create(deviceId);

	return std::make_unique<Keyboard>(kbType, std::move(ptrKbComms));
}