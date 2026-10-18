// Created by DeviceIoControl

#pragma once
#include "ILogger.h"

class ConsoleLogger
	: public ILogger
{
public:
	ConsoleLogger(HANDLE hConsoleOutput);

	ConsoleLogger();

	bool Write(LogLevel level, const std::wstring& output) override;

	~ConsoleLogger() override = default;

private:
	const HANDLE m_hConsoleOutput;
};