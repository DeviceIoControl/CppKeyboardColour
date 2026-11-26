// Created by DeviceIoControl

#pragma once
#include "LogLevel.h"
#include "ILogger.h"
#include "Translators/ITranslator.h"

class TranslatorFactory;

class Console
{
public:
	Console(std::unique_ptr<TranslatorFactory> pTranslatorFactory);
	Console();
	~Console() = default;

	bool CanLogOnLevel(LogLevel level) const;
	void SetTitle(const std::wstring& title, bool bLogTitle = true);

	void Hide();
	void Show();

	template<typename... _TArgs>
	bool Log(LogLevel level, const std::wstring& format, _TArgs&&... args)
	{
		if (this->IsVisible())
		{
			return this->WriteInternal(level, format, std::forward<_TArgs>(args)...);
		}

		return false;
	}

	void Prompt(const std::wstring& msg);

	bool IsVisible() const;

private:
	HWND m_hWnd{};
	LogLevel m_baseLoglevel{};
	std::mutex m_outputLock{};
	LANGID m_currentLanguage{};
	std::atomic<bool> m_isVisible = true;
	std::unique_ptr<ILogger> m_pLogger{};
	std::unique_ptr<ITranslator> m_pTranslator{};


	// The process will terminate when this function is called.
	[[noreturn]] void OnFatalMessage();

	template<typename ..._TArgs>
	std::wstring OnPreWrite(LogLevel level, const std::wstring& format, _TArgs&&... args)
	{
		const auto translatedLogLevel = m_pTranslator->Translate(level);
		const auto translatedPreFormatMsg = m_pTranslator->Translate(format);
		const auto translatedPostFormatMsg = xstd::format(translatedPreFormatMsg, std::forward<_TArgs>(args)...);

		return xstd::format(L"[%s]: %s", translatedLogLevel.c_str(), translatedPostFormatMsg.c_str());
	}

	template<typename ..._TArgs>
	bool WriteInternal(LogLevel level, const std::wstring& format, _TArgs&&... args)
	{
		if (!CanLogOnLevel(level))
		{
			return false; // ERROR: Cannot log on this level.
		}

		const auto logMessage = OnPreWrite(level, format, std::forward<_TArgs>(args)...);

		std::scoped_lock mutex_guard(m_outputLock);

		const auto bSuccess = m_pLogger->Write(level, logMessage);

		if (level == LogLevel::Fatal)
		{
			// point of no return.
			OnFatalMessage();
		}

		return bSuccess;
	}
};