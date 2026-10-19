// Created by DeviceIoControl

#pragma once
#include "LogLevel.h"
#include "ILogger.h"

class Console 
{
public:
	Console(LogLevel level = LogLevel::Debug);
	~Console() = default;

	void SetTitle(const std::wstring& title);

	void Hide();
	void Show();

	template<typename... _TArgs>
	bool Log(LogLevel level, const std::string& format, _TArgs&&... args)
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

	// The process will terminate when this function is called.
	[[noreturn]] void OnFatalMessage()
	{
		std::printf("\n%s\n", "Press ENTER to exit.");
		std::getchar();
		std::quick_exit(GetLastError());
	}

	inline bool CanLogOnLevel(LogLevel level) const
	{
		return (level >= m_baseLoglevel) ? true : false;
	}

	inline SYSTEMTIME GetCurrentSystemTime() const
	{
		SYSTEMTIME currentSysTime = { 0 };
		GetSystemTime(&currentSysTime);
		return currentSysTime;
	}

	template<typename ..._TArgs>
	bool WriteInternal(LogLevel level, const std::string& format, _TArgs&&... args)
	{
		if (CanLogOnLevel(level))
		{
			const auto strFormattedMsg = xstd::format(format, std::forward<_TArgs>(args)...);

			std::scoped_lock mutex_guard(m_outputLock);

			const auto bSuccess = m_pLogger->Write(level, strFormattedMsg);

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