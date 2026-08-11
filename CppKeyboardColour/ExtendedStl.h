// Created by DeviceIoControl

#pragma once
#include <cwctype>
#include "DeviceMask.h"

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