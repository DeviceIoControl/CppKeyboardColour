#pragma once

#include "pch.h"

struct __declspec(uuid("0c53fcfc-1d65-47dd-9733-9e99a283a238")) ICppKeyboardDevice
	: public IUnknown
{
public:
	virtual HRESULT GetDeviceID(uint32_t* puiDeviceId) const = 0;
};