// Created by DeviceIoControl
#pragma once

namespace Registry 
{
	std::wstring GetRegSzValue(HKEY hHive, const std::wstring& Path, const std::wstring& valueName);

} // namespace Registry