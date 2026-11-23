// Created by DeviceIoControl

#include "stdafx.h"
#include "PolishTranslator.h"

std::wstring PolishTranslator::Translate(const std::wstring& msg)
{
	return m_mapping[msg];
}

std::wstring PolishTranslator::Translate(LogLevel level)
{
	switch (level)
	{
	case LogLevel::Info:
		return L"Informacje";

	case LogLevel::Debug:
		return L"Odpluskwić";

	case LogLevel::Error:
		return L"Błąd";
		
	case LogLevel::Warning:
		return L"Ostrzeżenie";

	case LogLevel::Fatal:
		return L"Śmiertelny";
	}

	return L"???";
}

bool PolishTranslator::IsCompatible(LANGID langId) const
{
	return langId == MAKELANGID(LANG_POLISH, SUBLANG_POLISH_POLAND);
}