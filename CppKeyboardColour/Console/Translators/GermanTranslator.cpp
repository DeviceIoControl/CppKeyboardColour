// Created by DeviceIoControl

#include "stdafx.h"
#include "GermanTranslator.h"

std::wstring GermanTranslator::Translate(const std::wstring& msg)
{
	return m_mapping[msg];
}

std::wstring GermanTranslator::Translate(LogLevel level)
{
	switch (level)
	{
	case LogLevel::Info:
		return L"Info";

	case LogLevel::Debug:
		return L"Debuggen";

	case LogLevel::Error:
		return L"Fehler";
		
	case LogLevel::Warning:
		return L"Warnung";

	case LogLevel::Fatal:
		return L"Tödlich";
	}

	return L"???";
}

bool GermanTranslator::IsCompatible(LANGID langId) const
{
	return langId == MAKELANGID(LANG_GERMAN, SUBLANG_GERMAN)
		|| langId == MAKELANGID(LANG_GERMAN, SUBLANG_GERMAN_AUSTRIAN);
}