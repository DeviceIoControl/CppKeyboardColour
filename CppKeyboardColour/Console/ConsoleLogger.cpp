// Created by DeviceIoControl

#include "stdafx.h"
#include "ConsoleLogger.h"
#include "ConsoleColour.h"

namespace 
{
	bool OnWriteLoglevel(HANDLE hStdOutput, LogLevel level) 
	{
		DWORD charsWritten = 0;

		switch (level)
		{
		case LogLevel::Debug:
			SetConsoleTextAttribute(hStdOutput, xstd::to_underlying(ConsoleColour::LightGreen) & 0x0F);
			return WriteConsoleW(hStdOutput, L"<DEBUG>: ", 10, &charsWritten, nullptr);

		case LogLevel::Info:
			SetConsoleTextAttribute(hStdOutput, xstd::to_underlying(ConsoleColour::LightYellow) & 0x0F);
			return WriteConsoleW(hStdOutput, L"<INFO>: ", 9, &charsWritten, nullptr);

		case LogLevel::Warning:
			SetConsoleTextAttribute(hStdOutput, xstd::to_underlying(ConsoleColour::LightPurple) & 0x0F);
			return WriteConsoleW(hStdOutput, L"<WARNING>: ", 12, &charsWritten, nullptr);

		case LogLevel::Error:
			SetConsoleTextAttribute(hStdOutput, xstd::to_underlying(ConsoleColour::LightRed) & 0x0F);
			return WriteConsoleW(hStdOutput, L"<ERROR>: ", 10, &charsWritten, nullptr);

		case LogLevel::Fatal:
			SetConsoleTextAttribute(hStdOutput, xstd::to_underlying(ConsoleColour::LightRed) & 0x0F);
			return WriteConsoleW(hStdOutput, L"<FATAL>: ", 10, &charsWritten, nullptr);
		}

		return true;
	}

	bool OnWriteMessage(HANDLE hStdOutput, const std::wstring& msg)
	{
		DWORD charsWritten = 0;

		return WriteConsoleW(hStdOutput, msg.c_str(), static_cast<DWORD>(msg.size()) + 1, &charsWritten, nullptr)
			&& WriteConsoleW(hStdOutput, L"\n", 2, &charsWritten, nullptr)
			&& SetConsoleTextAttribute(hStdOutput, xstd::to_underlying(ConsoleColour::White) & 0x0F);
	}

} // namespace

ConsoleLogger::ConsoleLogger(HANDLE hConsoleOutput)
	: m_hConsoleOutput(hConsoleOutput)
{
}

ConsoleLogger::ConsoleLogger()
	: ConsoleLogger(GetStdHandle(STD_OUTPUT_HANDLE))
{
}

bool ConsoleLogger::Write(LogLevel level, const std::wstring& output)
{
	return OnWriteLoglevel(m_hConsoleOutput, level) && OnWriteMessage(m_hConsoleOutput, output);
}