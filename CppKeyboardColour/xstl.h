#pragma once
#include "stdafx.h"

namespace xstd 
{
	template<typename T>
	auto to_underlying(T enumType) 
	{
		return static_cast<std::underlying_type_t<T>>(enumType);
	}
} // namespace xstd 