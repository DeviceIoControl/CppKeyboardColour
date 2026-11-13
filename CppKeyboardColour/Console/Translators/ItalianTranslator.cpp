// Created by DeviceIoControl

#include "stdafx.h"
#include "ItalianTranslator.h"

std::wstring ItalianTranslator::Translate(const std::wstring& msg)
{
	return m_mapping[msg];
}

std::wstring ItalianTranslator::Translate(LogLevel level)
{
	switch (level)
	{
	case LogLevel::Info:
		return L"Informazioni";

	case LogLevel::Debug:
		return L"Debug";

	case LogLevel::Error:
		return L"Errore";
		
	case LogLevel::Warning:
		return L"Avvertimento";

	case LogLevel::Fatal:
		return L"Fatale";
	}

	return L"???";
}

bool ItalianTranslator::IsCompatible(LANGID langId) const
{
	return langId == MAKELANGID(LANG_ITALIAN, SUBLANG_ITALIAN);
}