#pragma once

#include "stdafx.h"

class ServiceControlHandler
{
public:
	ServiceControlHandler(const std::wstring& strServiceName, DWORD dwControlsAccepted, const std::vector<std::wstring>& arguments)
	{
		if (this->OnInitialise(arguments))
		{
			m_hServiceStatus = RegisterServiceCtrlHandlerExW(strServiceName.c_str(), &ServiceControlDispatcher, this);
			
			SERVICE_STATUS svcStatus{};

			svcStatus.dwWaitHint = 5000;
			svcStatus.dwCurrentState = SERVICE_ACTIVE;
			svcStatus.dwControlsAccepted = dwControlsAccepted;
			svcStatus.dwServiceType  = SERVICE_WIN32_OWN_PROCESS;
			
			SetServiceStatus(m_hServiceStatus, &svcStatus);
		}
	}

	bool OnContinue(DWORD dwEventType, LPVOID lpEventData)
	{
		return false;
	}

	bool OnPause(DWORD dwEventType, LPVOID lpEventData)
	{
		return false;
	}

	bool OnShutdown(DWORD dwEventType, LPVOID lpEventData)
	{
		return false;
	}

	bool OnStop(DWORD dwEventType, LPVOID lpEventData)
	{
		return false;
	}

	bool OnInterrogate(DWORD dwEventType, LPVOID lpEventData)
	{
		return false;
	}

	~ServiceControlHandler() = default;

private:
	SERVICE_STATUS_HANDLE m_hServiceStatus; // Does not need to be closed.

	bool OnInitialise(const std::vector<std::wstring>& strArguments) 
	{	
		return false;
	}

	static DWORD __stdcall ServiceControlDispatcher(DWORD dwControl, DWORD dwEventType, LPVOID lpEventData, LPVOID lpContext)
	{
		ServiceControlHandler* pThis =  static_cast<ServiceControlHandler*>(lpContext);

		switch (dwControl)
		{
		case SERVICE_CONTROL_CONTINUE:
			return pThis->OnContinue(dwEventType, lpEventData) ? NO_ERROR : GetLastError();

		case SERVICE_CONTROL_PAUSE:
			return pThis->OnPause(dwEventType, lpEventData) ? NO_ERROR : GetLastError();

		case SERVICE_CONTROL_SHUTDOWN:
			return pThis->OnShutdown(dwEventType, lpEventData) ? NO_ERROR : GetLastError();

		case SERVICE_CONTROL_STOP:
			return pThis->OnStop(dwEventType, lpEventData) ? NO_ERROR : GetLastError();
			
		case SERVICE_CONTROL_INTERROGATE:
			return pThis->OnInterrogate(dwEventType, lpEventData) ? NO_ERROR : GetLastError();
		}

		return ERROR_CALL_NOT_IMPLEMENTED;
	}
};

using ServiceControlHandlerPtr = std::shared_ptr<ServiceControlHandler>;