// Created by DeviceIoControl

#include "stdafx.h"
#include "DutchTranslator.h"

std::wstring DutchTranslator::Translate(const std::wstring& msg)
{
	return m_mapping[msg];
}

std::wstring DutchTranslator::Translate(LogLevel level)
{
	switch (level)
	{
	case LogLevel::Info:
		return L"Info";

	case LogLevel::Debug:
		return L"Fouten opsporen";

	case LogLevel::Error:
		return L"Fout";
		
	case LogLevel::Warning:
		return L"Waarschuwing";

	case LogLevel::Fatal:
		return L"Dodelijk";
	}

	return L"???";
}

bool DutchTranslator::IsCompatible(LANGID langId) const
{
	return langId == MAKELANGID(LANG_DUTCH, SUBLANG_DUTCH) 
		|| langId == MAKELANGID(LANG_DUTCH, SUBLANG_DUTCH_BELGIAN);
}