// Created by DeviceIoControl
#pragma once

#include "IKeyboardDevice.h"
#include "IKeyboardCommunicator.h"

class KeyboardCommunicatorFactory 
{
public:
	KeyboardCommunicatorFactory(std::shared_ptr<IKeyboardDevice> pKBDevice);

	std::shared_ptr<IKeyboardCommunicator> Create() const;

	~KeyboardCommunicatorFactory() = default;

private:
	std::shared_ptr<IKeyboardDevice> m_pKBDevice{};
};