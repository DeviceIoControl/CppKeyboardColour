// Created by DeviceIoControl
#pragma once

class Console 
{
public:
	Console();
	~Console() = default;

	void SetTitle(const std::wstring& title);

	void Prompt(const std::wstring& message);
	void Hide();
	void Show();

	bool IsVisible() const;

private:
	HWND m_hWnd{};
};
