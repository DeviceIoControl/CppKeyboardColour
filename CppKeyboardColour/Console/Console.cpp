// Created by DeviceIoControl

#include "stdafx.h"
#include "Console.h"
#include "ConsoleLogger.h"
#include "Translators/TranslatorFactory.h"

Console::Console(LogLevel level)
	: m_baseLoglevel(level)
{
	TranslatorFactory factory{};

	m_hWnd = GetConsoleWindow();
	m_pTranslator = factory.Create(GetUserDefaultLangID());
	m_pLogger = std::make_unique<ConsoleLogger>();
}

void Console::SetTitle(const std::wstring& title) 
{
	SetConsoleTitleW(title.c_str());
}

void Console::Hide() 
{
	ShowWindow(m_hWnd, this->IsVisible() ? SW_HIDE : SW_NORMAL);
}

void Console::Show() 
{
	ShowWindow(m_hWnd, !this->IsVisible() ? SW_SHOW : SW_NORMAL);
}

bool Console::IsVisible() const
{
	return !!(GetWindowLongPtrW(m_hWnd, GWL_STYLE) & WS_VISIBLE);
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
