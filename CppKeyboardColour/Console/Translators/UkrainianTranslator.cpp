// Created by DeviceIoControl

#include "stdafx.h"
#include "UkrainianTranslator.h"

std::wstring UkrainianTranslator::Translate(const std::wstring& msg)
{
	return m_mapping[msg];
}

std::wstring UkrainianTranslator::Translate(LogLevel level)
{
	switch (level)
	{
	case LogLevel::Info:
		return L"Інформація";

	case LogLevel::Debug:
		return L"Налагодження";

	case LogLevel::Error:
		return L"Помилка";
		
	case LogLevel::Warning:
		return L"УВАГА";

	case LogLevel::Fatal:
		return L"Смертельний";
	}

	return L"???";
}

bool UkrainianTranslator::IsCompatible(LANGID langId) const
{
	return langId == MAKELANGID(LANG_UKRAINIAN, SUBLANG_UKRAINIAN_UKRAINE);
}
