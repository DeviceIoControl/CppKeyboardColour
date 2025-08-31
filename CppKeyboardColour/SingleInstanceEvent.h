#pragma once

#include "stdafx.h"

bool IsSingleInstance() 
{
	HANDLE hInstance = CreateEventExW(nullptr, L"Global\\CLEVO_KBC_INSTANCE", CREATE_EVENT_INITIAL_SET, EVENT_ALL_ACCESS);
	auto const bIsSingleInstance = (GetLastError() == ERROR_ALREADY_EXISTS) ? false : true;

	CloseHandle(hInstance);

	return bIsSingleInstance;
}