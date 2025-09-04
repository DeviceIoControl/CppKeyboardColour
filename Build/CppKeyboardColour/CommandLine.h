// Created by DeviceIoControl

#pragma once

class CommandLine
{
public:
	static std::vector<std::wstring> GetCommandLines(size_t argc, const wchar_t** argv);
	static bool Contains(const std::wstring& toFind, const std::vector<std::wstring>& cmdlines);
};