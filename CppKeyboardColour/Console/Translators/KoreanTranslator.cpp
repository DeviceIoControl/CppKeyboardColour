// Created by DeviceIoControl

#include "stdafx.h"
#include "KoreanTranslator.h"

std::wstring KoreanTranslator::Translate(const std::wstring& msg)
{
	return m_mapping[msg];
}

std::wstring KoreanTranslator::Translate(LogLevel level)
{
	switch (level)
	{
	case LogLevel::Info:
		return L"정보";

	case LogLevel::Debug:
		return L"디버그";

	case LogLevel::Error:
		return L"오류";
		
	case LogLevel::Warning:
		return L"경고";

	case LogLevel::Fatal:
		return L"치명적인";
	}

	return L"???";
}

bool KoreanTranslator::IsCompatible(LANGID langId) const
{
	return langId == MAKELANGID(LANG_KOREAN, SUBLANG_KOREAN);
}
