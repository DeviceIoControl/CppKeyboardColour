// Created by DeviceIoControl

#include "stdafx.h"
#include "ChineseTraditionalTranslator.h"

std::wstring ChineseTraditionalTranslator::Translate(const std::wstring& msg)
{
	return m_mapping[msg];
}

std::wstring ChineseTraditionalTranslator::Translate(LogLevel level)
{
	switch (level)
	{
	case LogLevel::Info:
		return L"信息";

	case LogLevel::Debug:
		return L"调试";

	case LogLevel::Error:
		return L"错误";
		
	case LogLevel::Warning:
		return L"警告";

	case LogLevel::Fatal:
		return L"致命的";
	}

	return L"???";
}

bool ChineseTraditionalTranslator::IsCompatible(LANGID langId) const
{
	return langId == MAKELANGID(LANG_CHINESE_TRADITIONAL, SUBLANG_CHINESE_TRADITIONAL);
}
