// Created by DeviceIoControl

#pragma once

#include "IKeyboard.h"
#include "DeviceIdRetriever.h"

class KeyboardFactory 
{
public:
	KeyboardFactory() = default;

	std::unique_ptr<IKeyboard> Create() const;

	~KeyboardFactory() = default;

private:
#ifdef FAKE_KEYBOARD
	DeviceIdRetriever m_deviceIdRetriever{ true };
#else
	DeviceIdRetriever m_deviceIdRetriever{ false };
#endif
};
