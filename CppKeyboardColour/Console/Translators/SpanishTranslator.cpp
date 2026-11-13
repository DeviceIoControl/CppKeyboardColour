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

bool SpanishTranslator::IsCompatible(LANGID langId) const 
{
	return langId == MAKELANGID(LANG_SPANISH, SUBLANG_SPANISH)
		|| langId == MAKELANGID(LANG_SPANISH, SUBLANG_SPANISH_MODERN)
		|| langId == MAKELANGID(LANG_SPANISH, SUBLANG_SPANISH_GUATEMALA)
		|| langId == MAKELANGID(LANG_SPANISH, SUBLANG_SPANISH_COSTA_RICA)
		|| langId == MAKELANGID(LANG_SPANISH, SUBLANG_SPANISH_PANAMA)
		|| langId == MAKELANGID(LANG_SPANISH, SUBLANG_SPANISH_DOMINICAN_REPUBLIC)
		|| langId == MAKELANGID(LANG_SPANISH, SUBLANG_SPANISH_VENEZUELA)
		|| langId == MAKELANGID(LANG_SPANISH, SUBLANG_SPANISH_COLOMBIA)
		|| langId == MAKELANGID(LANG_SPANISH, SUBLANG_SPANISH_PERU)
		|| langId == MAKELANGID(LANG_SPANISH, SUBLANG_SPANISH_ARGENTINA)
		|| langId == MAKELANGID(LANG_SPANISH, SUBLANG_SPANISH_BOLIVIA)
		|| langId == MAKELANGID(LANG_SPANISH, SUBLANG_SPANISH_CHILE)
		|| langId == MAKELANGID(LANG_SPANISH, SUBLANG_SPANISH_US)
		|| langId == MAKELANGID(LANG_SPANISH, SUBLANG_SPANISH_ECUADOR)
		|| langId == MAKELANGID(LANG_SPANISH, SUBLANG_SPANISH_EL_SALVADOR)
		|| langId == MAKELANGID(LANG_SPANISH, SUBLANG_SPANISH_HONDURAS)
		|| langId == MAKELANGID(LANG_SPANISH, SUBLANG_SPANISH_NICARAGUA)
		|| langId == MAKELANGID(LANG_SPANISH, SUBLANG_SPANISH_PARAGUAY)
		|| langId == MAKELANGID(LANG_SPANISH, SUBLANG_SPANISH_PUERTO_RICO)
		|| langId == MAKELANGID(LANG_SPANISH, SUBLANG_SPANISH_URUGUAY);
}