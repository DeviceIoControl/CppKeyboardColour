#pragma once

#include "stdafx.h"
#include "Service.h"

static std::wstring g_strServiceName = L"CLEVO Keyboard Colour";
static ServiceControlHandlerPtr g_pServiceControlHandler;

VOID WINAPI ServiceMain(DWORD dwNumberOfArgs, LPWSTR* lpServiceArguments) 
{
	std::vector<std::wstring> serviceArguments(dwNumberOfArgs);

	for (size_t i = 0; i < dwNumberOfArgs; ++i) 
	{
		serviceArguments[i].assign(lpServiceArguments[i]);
	}

	g_pServiceControlHandler = std::make_shared<ServiceControlHandler>(g_strServiceName, serviceArguments);
}
