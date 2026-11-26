// Created by DeviceIoControl

#include "stdafx.h"
#include "Console.h"
#include "ConsoleLogger.h"
#include "../Utils/RegUtils.h"
#include "Translators/TranslatorFactory.h"

#define KB_CONFIG_REGKEY L"SOFTWARE\\CLEVO_KeyboardColour"
#define KB_CONFIG_TRANSLATION_VALUE L"EnableTranslations"
#define KB_CONFIG_CONSOLE_LOGLEVEL L"ConsoleLogLevel"

namespace
{
	bool IsTranslationEnabled()
	{
		return Registry::GetRegDWORDValue(HKEY_CURRENT_USER, KB_CONFIG_REGKEY, KB_CONFIG_TRANSLATION_VALUE).value_or(0) == 1;
	}

	LogLevel GetConsoleBaseLogLevel()
	{
		const auto level = Registry::GetRegDWORDValue(HKEY_CURRENT_USER, KB_CONFIG_REGKEY, KB_CONFIG_CONSOLE_LOGLEVEL);
		return static_cast<LogLevel>(std::min<uint32_t>(level.value_or(xstd::to_underlying(CONSOLE_BASE_LOGLEVEL)), xstd::to_underlying(LogLevel::Fatal)));
	}
} // namespace

Console::Console(std::unique_ptr<TranslatorFactory> pTranslatorFactory)
{
	SetConsoleOutputCP(CP_UTF16);

	m_currentLanguage = !IsTranslationEnabled()
		? MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_UK)
		: GetUserDefaultLangID();

	m_hWnd = GetConsoleWindow();
	m_baseLoglevel = GetConsoleBaseLogLevel();
	m_pLogger = std::make_unique<ConsoleLogger>();
	m_pTranslator = pTranslatorFactory->Create(m_currentLanguage);
	m_isVisible = IsWindowVisible(m_hWnd);
}

Console::Console()
	: Console(std::make_unique<TranslatorFactory>())
{
}

void Console::SetTitle(const std::wstring& title, bool bLogTitle /* = true */)
{
	const auto translatedTitle = m_pTranslator->Translate(title);
	std::ignore = SetConsoleTitleW(translatedTitle.c_str());

	if (bLogTitle)
	{
		if (!this->IsVisible())
		{
			this->Show();
		}

		std::ignore = m_pLogger->Write(LogLevel::None, translatedTitle + L"\n");
	}

	// Check if the current translator is compatible with the detected language ID.
	// If not, that means we are using the fallback language.
	// We confirm this by verifying the translator is any dialect of English (We check for British English).
	const auto isUsingFallbackLang = !m_pTranslator->IsCompatible(m_currentLanguage)
		&& m_pTranslator->IsCompatible(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_UK));

	if (isUsingFallbackLang)
	{
		this->Log(LogLevel::Warning, L"Current language is not supported, defaulting to English.");
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

void Console::Prompt(const std::wstring& msg)
{
	if (this->IsVisible())
	{
		const auto translatedPrompt = m_pTranslator->Translate(msg);
		m_pLogger->Write(LogLevel::None, translatedPrompt);
		std::ignore = std::getchar();
	}
}

bool Console::IsVisible() const
{
	return m_isVisible;
}

void Console::OnFatalMessage()
{
	this->Prompt(L"\nPress ENTER to exit.");
	std::exit(GetLastError());
}

bool Console::CanLogOnLevel(LogLevel level) const
{
	return (level >= m_baseLoglevel) ? true : false;
}