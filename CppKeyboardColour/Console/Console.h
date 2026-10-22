// Created by DeviceIoControl

#pragma once
#include "LogLevel.h"
#include "ILogger.h"
#include "Translators/ITranslator.h"

class Console
{
public:
	Console(LogLevel level = LogLevel::Debug);
	~Console() = default;

	void SetTitle(const std::wstring& title);

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

	bool IsVisible() const;

private:
	HWND m_hWnd{};
	LogLevel m_baseLoglevel;
	std::mutex m_outputLock{};
	std::unique_ptr<ILogger> m_pLogger;
	std::unique_ptr<ITranslator> m_pTranslator;

	// The process will terminate when this function is called.
	[[noreturn]] void OnFatalMessage();

	bool CanLogOnLevel(LogLevel level) const;

	SYSTEMTIME GetCurrentSystemTime() const;

	template<typename ..._TArgs>
	std::wstring OnPreFormatAndPreTranslation(LogLevel level, const std::wstring& format, _TArgs&&... args)
	{
		const auto translatedLogLevel = m_pTranslator->Translate(level);
		const auto translatedPreformatMsg = m_pTranslator->Translate(format);
		const auto translatedPostFormatMsg = xstd::format(translatedPreformatMsg, std::forward<_TArgs>(args)...);

		return xstd::format(L"[%s]: %s", translatedLogLevel.c_str(), translatedPostFormatMsg.c_str());
	}

	template<typename ..._TArgs>
	bool WriteInternal(LogLevel level, const std::wstring& format, _TArgs&&... args)
	{
		if (CanLogOnLevel(level))
		{
			const auto logMessage = OnPreFormatAndPreTranslation(level, format, std::forward<_TArgs>(args)...);

			std::scoped_lock mutex_guard(m_outputLock);

			const auto bSuccess = m_pLogger->Write(level, logMessage);

			if (level == LogLevel::Fatal)
			{
				// point of no return.
				OnFatalMessage();
			}

			return bSuccess;
		}

		return false; // ERROR: Cannot log on this level.
	}
};