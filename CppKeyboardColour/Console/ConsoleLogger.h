// Created by DeviceIoControl

#pragma once
#include "ILogger.h"
#include "Translators/ITranslator.h"

class ConsoleLogger
	: public ILogger
{
public:
	ConsoleLogger(HANDLE hConsoleOutput);
	ConsoleLogger();

	bool Write(LogLevel level, const std::wstring& logmsg) override;

	~ConsoleLogger() override = default;

private:
	HANDLE m_hConsoleOutput;
};