// Created by DeviceIoControl

#include "stdafx.h"
#include "RussianTranslator.h"

std::wstring RussianTranslator::Translate(const std::wstring& msg)
{
	return m_mapping[msg];
}

std::wstring RussianTranslator::Translate(LogLevel level)
{
	switch (level)
	{
	case LogLevel::Info:
		return L"ИНФОРМАЦИЯ";

	case LogLevel::Debug:
		return L"ОТЛАЖИВАТЬ";

	case LogLevel::Error:
		return L"ОШИБКА";
		
	case LogLevel::Warning:
		return L"ПРЕДУПРЕЖДЕНИЕ";

	case LogLevel::Fatal:
		return L"ФАТАЛЬНЫЙ";
	}

	return L"???";
}