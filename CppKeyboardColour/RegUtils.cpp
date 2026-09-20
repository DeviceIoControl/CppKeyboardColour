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

} // namespace Registry