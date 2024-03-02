#pragma once

#include "stdafx.h" 

class ServiceControlHandler
{
public:
	ServiceControlHandler(const std::wstring& strServiceName, const std::vector<std::wstring>& arguments)
	{
		RegisterServiceCtrlHandlerExW(strServiceName.c_str(), ServiceControlDispatcher, this);
	}

	bool OnContinue(DWORD dwEventType, LPVOID lpEventData)
	{
		
	}

	bool OnPause(DWORD dwEventType, LPVOID lpEventData)
	{

	}

	bool OnShutdown(DWORD dwEventType, LPVOID lpEventData)
	{

	}

	bool OnStop(DWORD dwEventType, LPVOID lpEventData)
	{

	}

	bool OnContinue(DWORD dwEventType, LPVOID lpEventData)
	{

	}


	bool OnInterrogate(DWORD dwEventType, LPVOID lpEventData)
	{

	}

private:


	static DWORD __stdcall ServiceControlDispatcher(DWORD dwControl, DWORD dwEventType, LPVOID lpEventData, LPVOID lpContext)
	{
		ServiceControlHandler* pThis =  static_cast<ServiceControlHandler*>(lpContext);

		switch (dwControl)
		{
		case SERVICE_CONTROL_CONTINUE:
			pThis->OnContinue(dwEventType, lpEventData);
			break;

		case SERVICE_CONTROL_PAUSE:
			pThis->OnPause(dwEventType, lpEventData);
			break;

		case SERVICE_CONTROL_SHUTDOWN:
			pThis->OnShutdown(dwEventType, lpEventData);
			break;

		case SERVICE_CONTROL_STOP:
			pThis->OnStop(dwEventType, lpEventData);
			break;

		case SERVICE_CONTROL_INTERROGATE:
			pThis->OnInterrogate(dwEventType, lpEventData);
			break;
		}
	}
};

using ServiceControlHandlerPtr = std::shared_ptr<ServiceControlHandler>;