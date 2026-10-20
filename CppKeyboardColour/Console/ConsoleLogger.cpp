// Created by DeviceIoControl

#include "stdafx.h"
#include "ConsoleLogger.h"
#include "ConsoleColour.h"

namespace
{
	bool OnWriteMessage(HANDLE hStdOutput, const std::wstring& msg)
	{
		DWORD charsWritten = 0;

		return WriteConsoleW(hStdOutput, msg.c_str(), static_cast<DWORD>(msg.size()) + 1, &charsWritten, nullptr)
			&& WriteConsoleW(hStdOutput, L"\n", 2, &charsWritten, nullptr)
			&& SetConsoleTextAttribute(hStdOutput, xstd::to_underlying(ConsoleColour::White) & 0x0F);
	}

	bool DoConsoleWrite(HANDLE hStdOutput, LogLevel level, const std::wstring& message)
	{
		DWORD charsWritten = 0;

		switch (level)
		{
		case LogLevel::Debug:
			SetConsoleTextAttribute(hStdOutput, xstd::to_underlying(ConsoleColour::LightGreen) & 0x0F);
			break;

		case LogLevel::Info:
			SetConsoleTextAttribute(hStdOutput, xstd::to_underlying(ConsoleColour::LightYellow) & 0x0F);
			break;

		case LogLevel::Warning:
			SetConsoleTextAttribute(hStdOutput, xstd::to_underlying(ConsoleColour::LightPurple) & 0x0F);
			break;

		case LogLevel::Error:
			SetConsoleTextAttribute(hStdOutput, xstd::to_underlying(ConsoleColour::LightRed) & 0x0F);
			break;

		case LogLevel::Fatal:
			SetConsoleTextAttribute(hStdOutput, xstd::to_underlying(ConsoleColour::LightRed) & 0x0F);
			WriteConsoleW(hStdOutput, L"\n", 2, &charsWritten, nullptr);
			break;
		}

		return OnWriteMessage(hStdOutput, message);
	}

} // namespace

ConsoleLogger::ConsoleLogger(HANDLE hConsoleOutput, std::unique_ptr<ITranslator> pTranslator)
	: BaseLogger(std::move(pTranslator))
{
	m_hConsoleOutput = hConsoleOutput;
}

ConsoleLogger::ConsoleLogger(std::unique_ptr<ITranslator> pTranslator)
	: ConsoleLogger(GetStdHandle(STD_OUTPUT_HANDLE), std::move(pTranslator))
{
}

bool ConsoleLogger::OnWrite(LogLevel level, const std::wstring& logmsg)
{
	return DoConsoleWrite(m_hConsoleOutput, level, logmsg);
}