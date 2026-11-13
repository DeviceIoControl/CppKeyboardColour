// Created by DeviceIoControl

#include "stdafx.h"
#include "RegUtils.h"

namespace Registry 
{
	std::wstring GetRegSzValue(HKEY hHive, const std::wstring& path, const std::wstring& valueName)
	{
		DWORD stringLength = 0;
		RegGetValueW(hHive, path.c_str(), valueName.c_str(), RRF_RT_REG_SZ, nullptr, nullptr, &stringLength);

		if (!stringLength)
		{
			return {};
		}

		std::wstring regSzValue(stringLength, 0);
		if (RegGetValueW(hHive, path.c_str(), valueName.c_str(), RRF_RT_REG_SZ, nullptr, regSzValue.data(), &stringLength) != ERROR_SUCCESS) 
		{
			return {};
		}

		return regSzValue;
	}

	std::optional<uint32_t> GetRegDWORDValue(HKEY hHive, const std::wstring& path, const std::wstring& valueName) 
	{
		DWORD regDwordValue = 0;
		if (RegGetValueW(hHive, path.c_str(), valueName.c_str(), RRF_RT_REG_DWORD, nullptr, &regDwordValue, nullptr) != ERROR_SUCCESS) 
		{
			return std::nullopt;
		}

		return regDwordValue;
	}
} // namespace Registry