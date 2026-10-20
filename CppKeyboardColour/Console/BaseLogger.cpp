// Created by DeviceIoControl

#include "stdafx.h"
#include "BaseLogger.h"
#include "Translators/EnglishTranslator.h"

BaseLogger::BaseLogger(std::unique_ptr<ITranslator> pTranslator)
	: m_pTranslator(std::move(pTranslator))
{
}

BaseLogger::BaseLogger()
	: BaseLogger(std::make_unique<EnglishTranslator>())
{
}

bool BaseLogger::Write(LogLevel level, const std::wstring& msg) /* final */
{
	const auto translatedLogLevel = m_pTranslator->Translate(level);
	const auto translatedMessage = m_pTranslator->Translate(msg);
	const auto logMessage = xstd::format("[%S]: %S", translatedLogLevel.c_str(), translatedMessage.c_str());

	return this->OnWrite(level, logMessage);
}