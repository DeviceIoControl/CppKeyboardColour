// Created by DeviceIoControl

#include "stdafx.h"
#include "Console.h"
#include "ConsoleLogger.h"
#include "../Utils/RegUtils.h"
#include "Translators/TranslatorFactory.h"

#define KB_CONFIG_REGKEY L"SOFTWARE\\CLEVO_KeyboardColour"
#define KB_CONFIG_TRANSLATION_VALUE L"EnableTranslation"

namespace 
{
	bool IsTranslationEnabled()
	{
		return Registry::GetRegDWORDValue(HKEY_CURRENT_USER, KB_CONFIG_REGKEY, KB_CONFIG_TRANSLATION_VALUE).value_or(0) == 1;
	}

} // namespace 

Console::Console(LogLevel level)
	: m_baseLoglevel(level)
{
	TranslatorFactory factory{};
	SetConsoleOutputCP(CP_UTF16);

	m_currentLanguage = !IsTranslationEnabled()
		? MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_UK)
		: GetUserDefaultLangID();

	m_hWnd = GetConsoleWindow();
	m_pTranslator = factory.Create(m_currentLanguage);
	m_pLogger = std::make_unique<ConsoleLogger>();
}

void Console::SetTitle(const std::wstring& title) 
{
	const auto translatedTitle = m_pTranslator->Translate(title).append(L"\n");
	SetConsoleTitleW(translatedTitle.c_str());

	m_pLogger->Write(LogLevel::None, translatedTitle);

	// Check if the current translator is compatible with the detected language ID.
	// If not, that means we are using the fallback language. 
	// We confirm this by verifying the translator is any dialect of English (We check for British English).
	const auto isUsingFallbackLang = !m_pTranslator->IsCompatible(m_currentLanguage)
		&& m_pTranslator->IsCompatible(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_UK));

	if (isUsingFallbackLang)
	{
		m_pLogger->Write(LogLevel::Warning, L"Current language is not supported, defaulting to English.");
	}
}

void Console::Hide()
{
	m_isVisible = !ShowWindow(m_hWnd, this->IsVisible() ? SW_HIDE : SW_NORMAL);
}

void Console::Show() 
{
	m_isVisible = ShowWindow(m_hWnd, !this->IsVisible() ? SW_SHOW : SW_NORMAL);
}

bool Console::IsVisible() const
{
	return m_isVisible;
}

void Console::OnFatalMessage()
{
	std::printf("\n%s\n", "Press ENTER to exit.");
	std::getchar();
	std::quick_exit(GetLastError());
}

bool Console::CanLogOnLevel(LogLevel level) const
{
	return (level >= m_baseLoglevel) ? true : false;
}

SYSTEMTIME Console::GetCurrentSystemTime() const
{
	SYSTEMTIME currentSysTime = { 0 };
	GetSystemTime(&currentSysTime);
	return currentSysTime;
}