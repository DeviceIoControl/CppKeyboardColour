// Created by DeviceIoControl

#include "stdafx.h"
#include "SpanishTranslator.h"

std::wstring SpanishTranslator::Translate(const std::wstring& msg)
{
	return m_mapping[msg];
}

std::wstring SpanishTranslator::Translate(LogLevel level)
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