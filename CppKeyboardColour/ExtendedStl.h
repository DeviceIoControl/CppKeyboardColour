// Created by DeviceIoControl

#pragma once
#include <cwctype>
#include "DeviceMask.h"

namespace xstd
{
	inline std::wstring to_upper_case(const std::wstring& str)
	{
		std::wstring upper_case(str.length(), NULL);
		std::transform(str.cbegin(), str.cend(), upper_case.begin(), std::towupper);
		return upper_case;
	}

	inline std::wstring to_lower_case(const std::wstring& str)
	{
		std::wstring lower_case(str.length(), NULL);
		std::transform(str.cbegin(), str.cend(), lower_case.begin(), std::towlower);
		return lower_case;
	}

	template<typename _Ty>
	inline constexpr std::underlying_type_t<_Ty> to_underlying(_Ty value)
	{
		return static_cast<std::underlying_type_t<_Ty>>(value);
	}

	inline std::optional<uint32_t> stoi(const std::wstring& input, int32_t base = 10)
	{
		try
		{
			return std::stoul(input, nullptr, base);
		}
		catch (...)
		{
			return std::nullopt;
		}
	}

} // namespace xstd

inline bool operator&(DeviceMask a, DeviceMask b) 
{
	return (xstd::to_underlying(a) & xstd::to_underlying(b)) != 0;
}

inline DeviceMask operator|(DeviceMask a, DeviceMask b)
{
	return static_cast<DeviceMask>(xstd::to_underlying(a) | xstd::to_underlying(b));
}

inline DeviceMask operator|=(DeviceMask a, DeviceMask b)
{
	return static_cast<DeviceMask>(xstd::to_underlying(a) | xstd::to_underlying(b));
}

inline bool operator!(DeviceMask a)
{
	return xstd::to_underlying(a) != 0;
}