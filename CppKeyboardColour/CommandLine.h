// Created by DeviceIoControl

#pragma once

class CommandLine
{
public:
	static std::vector<std::wstring> GetCommandLines(size_t argc, const wchar_t** argv);
	static bool Contains(const std::wstring& toFind, const std::vector<std::wstring>& cmdlines);

	// The command-line must only contain 1 of the commands specified in 'toFind'
	static bool ExclusiveContains(const std::vector<std::wstring>& toFind, const std::vector<std::wstring>& cmdlines);
	static std::vector<std::wstring> GetCommandsAfter(const std::wstring& toFind, const std::vector<std::wstring>& cmdlines);
};