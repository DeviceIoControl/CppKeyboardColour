// Created by DeviceIoControl

#include "stdafx.h"
#include "FrenchTranslator.h"

std::wstring FrenchTranslator::Translate(const std::wstring& msg)
{
	return m_mapping[msg];
}

std::wstring FrenchTranslator::Translate(LogLevel level)
{
	switch (level)
	{
	case LogLevel::Info:
		return L"Infos";

	case LogLevel::Debug:
		return L"Déboguer";

	case LogLevel::Error:
		return L"Erreur";
		
	case LogLevel::Warning:
		return L"Avertissement";

	case LogLevel::Fatal:
		return L"Fatal";
	}

	return L"???";
}