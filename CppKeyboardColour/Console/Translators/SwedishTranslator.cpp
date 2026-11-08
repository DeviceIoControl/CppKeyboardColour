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
		return L"Info";

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