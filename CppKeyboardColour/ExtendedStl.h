// Created by DeviceIoControl

#pragma once
#include "Devices/DeviceMask.h"

namespace xstd
{
	template<typename _Ty>
	using _TPointer = typename std::enable_if<std::is_pointer_v<_Ty>, _Ty>::type;

	template<typename _Ty>
	using _TInteger = typename std::enable_if<std::numeric_limits<_Ty>::is_integer, _Ty>::type;

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

	template<typename _TRet = uintptr_t, typename _Ty>
	constexpr _TInteger<_TRet> ptr_to_integer(_Ty ptr)
	{
		static_assert(std::is_pointer<_Ty>::value, "ptr must be a pointer type.");
		static_assert(std::numeric_limits<_TRet>::is_integer, "return type must be of an integer type.");

		return reinterpret_cast<_TRet>(ptr);
	}

	template<typename _TRet = void*, typename _Ty>
	constexpr _TPointer<_TRet> integer_to_ptr(_Ty intptr)
	{
		static_assert(std::numeric_limits<_Ty>::is_integer, "intptr must be an integer type.");
		static_assert(std::is_pointer<_TRet>::value, "return type must be of a pointer type.");

		return reinterpret_cast<_TRet>(intptr);
	}

	template<typename _TyRet = void, typename _Ty>
	constexpr _TyRet* adjust_ptr(const _Ty* ptr, size_t byte_offset)
	{
		return xstd::integer_to_ptr<_TyRet*>(xstd::ptr_to_integer(ptr) + byte_offset);
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

	template<typename ..._TArgs>
	std::wstring format(const std::string& format, _TArgs&& ...args)
	{
		std::string allocated_string(0x7fff, 0);

		const auto length = std::snprintf(nullptr, 0, format.c_str(), std::forward<_TArgs>(args)...);

		if (allocated_string.size() < length)
		{
			allocated_string.resize(length);
		}

		std::sprintf(allocated_string.data(), format.c_str(), std::forward<_TArgs>(args)...);

		allocated_string.shrink_to_fit();

		return std::wstring{ allocated_string.cbegin(), allocated_string.cend() };
	}

	enum class date_format : uint16_t
	{
		dd_mm_yyyy,
		mm_dd_yyyy,
		yyyy_mm_dd,
		dd_mm_yy,
		mm_dd_yy,
		yy_mm_dd
	};

	inline std::wstring to_wstring(const SYSTEMTIME& sys_time, date_format date_form = date_format::dd_mm_yyyy)
	{
		switch (date_form)
		{
		case date_format::dd_mm_yyyy:
			return xstd::format("%02d/%02d/%04d - %02d:%02d:%02d.%04d",
				sys_time.wDay, sys_time.wMonth, sys_time.wYear, sys_time.wHour, sys_time.wMinute, sys_time.wSecond, sys_time.wMilliseconds);

		case date_format::mm_dd_yyyy:
			return xstd::format("%02d/%02d/%04d - %02d:%02d:%02d.%04d",
				sys_time.wMonth, sys_time.wDay, sys_time.wYear, sys_time.wHour, sys_time.wMinute, sys_time.wSecond, sys_time.wMilliseconds);

		case date_format::yyyy_mm_dd:
			return xstd::format("%04d/%02d/%02d - %02d:%02d:%02d.%04d",
				sys_time.wYear, sys_time.wMonth, sys_time.wDay, sys_time.wHour, sys_time.wMinute, sys_time.wSecond, sys_time.wMilliseconds);

		case date_format::dd_mm_yy:
			return xstd::format("%02d/%02d/%02d - %02d:%02d:%02d.%04d",
				sys_time.wDay, sys_time.wMonth, sys_time.wYear, sys_time.wHour, sys_time.wMinute, sys_time.wSecond, sys_time.wMilliseconds);

		case date_format::mm_dd_yy:
			return xstd::format("%02d/%02d/%02d - %02d:%02d:%02d.%04d",
				sys_time.wMonth, sys_time.wDay, sys_time.wYear, sys_time.wHour, sys_time.wMinute, sys_time.wSecond, sys_time.wMilliseconds);

		case date_format::yy_mm_dd:
			return xstd::format("%02d/%02d/%02d - %02d:%02d:%02d.%04d",
				sys_time.wYear, sys_time.wMonth, sys_time.wDay, sys_time.wHour, sys_time.wMinute, sys_time.wSecond, sys_time.wMilliseconds);
		}

		return {};
	}

	constexpr float lerp(float a, float b, float t) noexcept
	{
		return static_cast<float>(t == 1 ? b : (t * b + (1 - t) * a));
	}

} // namespace xstd

inline bool operator&(DeviceMask a, DeviceMask b)
{
	return (xstd::to_underlying(a) & xstd::to_underlying(b)) != 0;
}

inline void operator&=(DeviceMask& a, DeviceMask b)
{
	a = static_cast<DeviceMask>(xstd::to_underlying(a) & xstd::to_underlying(b));
}

inline DeviceMask operator|(DeviceMask a, DeviceMask b)
{
	return static_cast<DeviceMask>(xstd::to_underlying(a) | xstd::to_underlying(b));
}

inline void operator|=(DeviceMask& a, DeviceMask b)
{
	a = static_cast<DeviceMask>(xstd::to_underlying(a) | xstd::to_underlying(b));
}

inline bool operator!(DeviceMask a)
{
	return xstd::to_underlying(a) != 0;
}