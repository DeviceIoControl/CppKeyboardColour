// Created by DeviceIoControl

#include "stdafx.h"
#include "SwedishTranslator.h"

std::wstring SwedishTranslator::Translate(const std::wstring& msg)
{
	return m_mapping[msg];
}

std::wstring SwedishTranslator::Translate(LogLevel level)
{
	switch (level)
	{
	case LogLevel::Info:
		return L"Uppgifter";

	case LogLevel::Debug:
		return L"Felsök";

	case LogLevel::Error:
		return L"Fel";
		
	case LogLevel::Warning:
		return L"Varning";

	case LogLevel::Fatal:
		return L"Dödlig";
	}

	return L"???";
}

bool SwedishTranslator::IsCompatible(LANGID langId) const 
{
	return langId == MAKELANGID(LANG_SWEDISH, SUBLANG_SWEDISH)
		|| langId == MAKELANGID(LANG_SWEDISH, SUBLANG_SWEDISH_FINLAND);
}