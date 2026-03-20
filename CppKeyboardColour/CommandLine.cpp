// Created by DeviceIoControl

#include "stdafx.h"
#include "CommandLine.h"

/*static*/ std::vector<std::wstring> CommandLine::GetCommandLines(size_t argc, const wchar_t** argv)
{
	std::vector<std::wstring> cmdLines{};

	for (size_t i = 1; i < argc; ++i)
	{
		cmdLines.emplace_back(xstd::to_lower_case(argv[i]));
	}

	return cmdLines;
}

/*static*/ bool CommandLine::Contains(const std::wstring& toFind, const std::vector<std::wstring>& cmdlines)
{
	return std::find_if(cmdlines.cbegin(), cmdlines.cend(), [&toFind](const auto& cmdLine) 
		{ 
			return cmdLine == toFind;
		}) != cmdlines.cend();
}

/* static */ bool CommandLine::ExclusiveContains(const std::vector<std::wstring>& toFind, const std::vector<std::wstring>& cmdlines) 
{
	bool isFound = false;

	for (auto const& current : toFind)
	{
		if (isFound && CommandLine::Contains(current, cmdlines))
		{
			return false;
		}

		if (!isFound && CommandLine::Contains(current, cmdlines)) 
		{
			isFound = true;
		}
	}

	return isFound;
}

/*static*/ std::vector<std::wstring> CommandLine::GetCommandsAfter(const std::wstring& toFind, const std::vector<std::wstring>& cmdLines)
{
	bool foundCommand = false;
	std::vector<std::wstring> followingCmds{};
	auto const _toFind = xstd::to_lower_case(toFind);

	for (auto const& currentCmd : cmdLines) 
	{
		if (!foundCommand && currentCmd == _toFind)
		{
			foundCommand = true;
			continue;
		}

		if (foundCommand)
		{
			followingCmds.push_back(currentCmd);
		}
	}

	return followingCmds;
}