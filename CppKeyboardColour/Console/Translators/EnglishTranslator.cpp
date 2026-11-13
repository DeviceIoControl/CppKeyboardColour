// Created by DeviceIoControl

#include "stdafx.h"
#include "EnglishTranslator.h"

std::wstring EnglishTranslator::Translate(const std::wstring& msg)
{
	return msg;
}

std::wstring EnglishTranslator::Translate(LogLevel level) 
{
	switch (level) 
	{
	case LogLevel::Info:
		return L"INFO";

	case LogLevel::Debug:
		return L"DEBUG";

	case LogLevel::Error:
		return L"ERROR";

	case LogLevel::Warning:
		return L"WARNING";

	case LogLevel::Fatal:
		return L"FATAL";
	}

	return L"???";
}

bool EnglishTranslator::IsCompatible(LANGID langId) const
{
	return langId == MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_AUS)
		|| langId == MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US)
		|| langId == MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_UK)
		|| langId == MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_CAN)
		|| langId == MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_CARIBBEAN)
		|| langId == MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_TRINIDAD)
		|| langId == MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_BELIZE)
		|| langId == MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_INDIA)
		|| langId == MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_JAMAICA)
		|| langId == MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_NZ)
		|| langId == MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_SINGAPORE)
		|| langId == MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_ZIMBABWE)
		|| langId == MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_MALAYSIA)
		|| langId == MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_PHILIPPINES)
		|| langId == MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_SOUTH_AFRICA)
		|| langId == MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_EIRE);
}