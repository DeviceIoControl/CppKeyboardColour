// Created by DeviceIoControl

#pragma once
#include "BaseLogger.h"
#include "Translators/ITranslator.h"

class ConsoleLogger
	: public BaseLogger
{
public:
	ConsoleLogger(HANDLE hConsoleOutput, std::unique_ptr<ITranslator> pTranslator);
	ConsoleLogger(std::unique_ptr<ITranslator> pTranslator);

	~ConsoleLogger() override = default;

private:
	HANDLE m_hConsoleOutput;

	bool OnWrite(LogLevel level, const std::wstring& logmsg) override;
};