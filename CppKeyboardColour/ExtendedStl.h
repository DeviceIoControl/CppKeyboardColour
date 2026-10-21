// Created by DeviceIoControl

#pragma once
#include "Devices/DeviceMask.h"
#include "Common/KeyboardType.h"

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
	int snwprintf(wchar_t* _Buffer, size_t _BufferCount, wchar_t const* _Format, _TArgs&& ...args)
	{
		return _snwprintf(_Buffer, _BufferCount, _Format, args...);
	}

	template<typename ..._TArgs>
	int swprintf(wchar_t* _Buffer, wchar_t const* _Format, _TArgs&& ...args)
	{
		return _swprintf(_Buffer, _Format, args...);
	}

	template<typename ..._TArgs>
	std::wstring format(const std::wstring& format, _TArgs&& ...args)
	{
		std::wstring allocated_string(0x7fff, 0);

		const auto length = xstd::snwprintf(nullptr, 0, format.c_str(), std::forward<_TArgs>(args)...);

		if (length == 0xffffffff) 
		{
			return L"";
		}

		if (allocated_string.size() < length)
		{
			allocated_string.resize(length);
		}

		xstd::swprintf(allocated_string.data(), format.c_str(), std::forward<_TArgs>(args)...);

		allocated_string.shrink_to_fit();

		return allocated_string;
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

namespace xstd 
{
	inline std::wstring to_wstring(KeyboardType kbType)
	{
		switch (kbType)
		{
		case KeyboardType::SINGLE_ZONE:
			return L"Single Zone";

		case KeyboardType::TRIPLE_ZONE:
			return L"Triple Zone";

		case KeyboardType::PER_KEY:
			return L"Per-Key";
		}

		return L"";
	}

	inline std::wstring to_wstring(DeviceMask devices)
	{
		std::wstring result{};

		if (!!(devices & DeviceMask::Keyboard))
		{
			result.append(L"[Keyboard] ");
		}

		if (!!(devices & DeviceMask::Lightbar))
		{
			result.append(L"[Lightbar] ");
		}

		if (!!(devices & DeviceMask::Logo))
		{
			result.append(L"[Logo] ");
		}

		return result;
	}

} // namespace 