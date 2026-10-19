// Created by DeviceIoControl

#include "stdafx.h"
#include "Console.h"
#include "ConsoleLogger.h"

Console::Console(LogLevel level) 
	: m_baseLoglevel(level)
{
	m_pLogger = std::make_unique<ConsoleLogger>();
	m_hWnd = GetConsoleWindow();
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
