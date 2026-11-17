// Created by DeviceIoControl

#include "stdafx.h"
#include "ChineseSimplifiedTranslator.h"

std::wstring ChineseSimplifiedTranslator::Translate(const std::wstring& msg)
{
	return m_mapping[msg];
}

std::wstring ChineseSimplifiedTranslator::Translate(LogLevel level)
{
	switch (level)
	{
	case LogLevel::Info:
		return L"資訊";

	case LogLevel::Debug:
		return L"偵錯";

	case LogLevel::Error:
		return L"錯誤";
		
	case LogLevel::Warning:
		return L"警告";

	case LogLevel::Fatal:
		return L"致命的";
	}

	return L"???";
}

bool ChineseSimplifiedTranslator::IsCompatible(LANGID langId) const
{
	return langId == MAKELANGID(LANG_CHINESE_SIMPLIFIED, SUBLANG_CHINESE_SIMPLIFIED);
}
