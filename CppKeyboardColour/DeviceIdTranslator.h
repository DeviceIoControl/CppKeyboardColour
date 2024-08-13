// Created by DeviceIoControl

#pragma once

#include "stdafx.h"
#include "DeviceIds.h"
#include "KeyboardType.h"

class DeviceIdTranslator
{
public:
	DeviceIdTranslator() = default;

	KeyboardType TranslateToKBType(uint32_t deviceId) const
	{
		if (IsTripleZoneKeyboard(deviceId))
		{
			return KeyboardType::TRIPLE_ZONE;
		}

		if (IsSingleZoneKeyboard(deviceId))
		{
			return KeyboardType::SINGLE_ZONE;
		}

		return KeyboardType::NONE;
	}

	~DeviceIdTranslator() = default;

private:
	inline bool IsSingleZoneKeyboard(uint32_t deviceId) const
	{
		static const std::set<uint32_t> s_singleZoneKeyboards = {
			DEVICE_ID_NP50SXX
		};

		return s_singleZoneKeyboards.find(deviceId) != s_singleZoneKeyboards.cend();
	}

	inline bool IsTripleZoneKeyboard(uint32_t deviceId) const
	{
		static const std::set<uint32_t> s_tripleZoneKeyboards = {
			DEVICE_ID_P650RS_G
		};

		return s_tripleZoneKeyboards.find(deviceId) != s_tripleZoneKeyboards.cend();
	}
};