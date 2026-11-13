// Created by DeviceIoControl
#pragma once

namespace Registry 
{
	std::wstring GetRegSzValue(HKEY hHive, const std::wstring& Path, const std::wstring& valueName);
	std::optional<uint32_t> GetRegDWORDValue(HKEY hHive, const std::wstring& Path, const std::wstring& valueName);
} // namespace Registry