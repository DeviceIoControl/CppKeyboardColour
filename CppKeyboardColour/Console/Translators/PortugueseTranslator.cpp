// Created by DeviceIoControl

#include "stdafx.h"
#include "PortugueseTranslator.h"

std::wstring PortugueseTranslator::Translate(const std::wstring& msg)
{
	return m_mapping[msg];
}

std::wstring PortugueseTranslator::Translate(LogLevel level)
{
	switch (level)
	{
	case LogLevel::Info:
		return L"Informações";

	case LogLevel::Debug:
		return L"Depurar";

	case LogLevel::Error:
		return L"Erro";

	case LogLevel::Warning:
		return L"Aviso";

	case LogLevel::Fatal:
		return L"funesto";
	}

	return L"???";
}

bool PortugueseTranslator::IsCompatible(LANGID langId) const
{
	return langId == MAKELANGID(LANG_PORTUGUESE, SUBLANG_PORTUGUESE)
		|| langId == MAKELANGID(LANG_PORTUGUESE, SUBLANG_PORTUGUESE_BRAZILIAN);
}