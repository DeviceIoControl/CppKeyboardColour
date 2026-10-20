// Created by DeviceIoControl

#pragma once

#include "ILogger.h"
#include "Translators/ITranslator.h"

class BaseLogger 
	: public ILogger
{
public:
	BaseLogger(std::unique_ptr<ITranslator> pTranslator);
	BaseLogger();

	~BaseLogger() override = default;

	bool Write(LogLevel level, const std::wstring& msg) final;

protected:
	virtual bool OnWrite(LogLevel level, const std::wstring& logmsg) = 0;

private:
	std::unique_ptr<ITranslator> m_pTranslator;
};
