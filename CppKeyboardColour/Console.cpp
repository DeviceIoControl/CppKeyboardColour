// Created by DeviceIoControl

#include "stdafx.h"
#include "Console.h"

Console::Console() 
{
	m_hWnd = GetConsoleWindow();
}

void Console::SetTitle(const std::wstring& title) 
{
	SetConsoleTitleW(title.c_str());
}

void Console::Prompt(const std::wstring& message)
{
	if (this->IsVisible())
	{
		std::wcout << message << "\n";
		std::getchar();
	}
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
