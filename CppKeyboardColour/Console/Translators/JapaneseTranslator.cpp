// Created by DeviceIoControl

#include "stdafx.h"
#include "JapaneseTranslator.h"

std::wstring JapaneseTranslator::Translate(const std::wstring& msg)
{
	return m_mapping[msg];
}

std::wstring JapaneseTranslator::Translate(LogLevel level)
{
	switch (level)
	{
	case LogLevel::Info:
		return L"情報";

	case LogLevel::Debug:
		return L"デバッグ";

	case LogLevel::Error:
		return L"エラー";
		
	case LogLevel::Warning:
		return L"警告";

	case LogLevel::Fatal:
		return L"フェータル";
	}

	return L"???";
}

bool JapaneseTranslator::IsCompatible(LANGID langId) const
{
	return langId == MAKELANGID(LANG_JAPANESE, SUBLANG_JAPANESE_JAPAN);
}
