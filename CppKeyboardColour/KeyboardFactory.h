// Created by DeviceIoControl

#pragma once

#include "IKeyboard.h"
#include "IKeyboardDevice.h"

class KeyboardFactory 
{
public:
	KeyboardFactory(bool fakeKeyboard = false);

	std::unique_ptr<IKeyboard> Create() const;

	~KeyboardFactory() = default;

private:
	std::shared_ptr<IKeyboardDevice> m_pKBDevice;
};
