// Created by DeviceIoControl

#include "stdafx.h"
#include "KeyboardFactory.h"
#include "Keyboard.h"
#include "KeyboardDevice.h"
#include "KeyboardCommunicatorFactory.h"

namespace 
{
	std::ostream& operator<<(std::ostream& _Ostr, KeyboardType kbType)
	{
		switch (kbType) 
		{
		case KeyboardType::SINGLE_ZONE:
			return _Ostr << "Single Zone";

		case KeyboardType::TRIPLE_ZONE:
			return _Ostr << "Triple Zone";

		case KeyboardType::TRIPLE_ZONE_LIGHTBAR:
			return _Ostr << "Triple Zone (with Lightbar)";
		}

		return _Ostr << "Not supported";
	}

} // namespace 

KeyboardFactory::KeyboardFactory(bool fakeKeyboard /*= false*/)
	: m_pKBDevice(std::make_unique<KeyboardDevice>(fakeKeyboard))
{
}

std::unique_ptr<IKeyboard> KeyboardFactory::Create() const 
{
	if (!m_pKBDevice) 
	{
		return nullptr;
	}

	auto const deviceId = m_pKBDevice->GetDeviceId();
	const auto kbType = m_pKBDevice->GetKeyboardType();

	std::cout << "Detected Device ID: 0x" << (void*)deviceId << "\n";
	std::cout << "Keyboard Type: " << kbType << "\n";

	if (kbType == KeyboardType::NONE)
	{
		return nullptr;
	}

	KeyboardCommunicatorFactory const kbCommFactory(m_pKBDevice);
	return std::make_unique<Keyboard>(m_pKBDevice, kbCommFactory.Create());
}