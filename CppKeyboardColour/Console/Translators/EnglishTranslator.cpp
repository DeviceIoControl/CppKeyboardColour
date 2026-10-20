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