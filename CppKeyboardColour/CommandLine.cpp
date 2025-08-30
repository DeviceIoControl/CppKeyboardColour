// Created by DeviceIoControl

#include "stdafx.h"
#include "CommandLine.h"

/*static*/ std::vector<std::wstring> CommandLine::GetCommandLines(size_t argc, const wchar_t** argv)
{
	std::vector<std::wstring> cmdLines{};

	for (size_t i = 1; i < argc; ++i)
	{
		cmdLines.emplace_back(argv[i]);
	}

	return cmdLines;
}

/*static*/ bool CommandLine::Contains(const std::wstring& toFind, const std::vector<std::wstring>& cmdlines)
{
	return std::find_if(cmdlines.cbegin(), cmdlines.cend(), [&toFind](const auto& cmdLine) {
		return _wcsicmp(cmdLine.c_str(), toFind.c_str()) == 0;
		}) != cmdlines.cend();
}
