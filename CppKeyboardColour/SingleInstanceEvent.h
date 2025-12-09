#pragma once

#include "stdafx.h"

#define SINGLE_INSTANCE_NAME L"Global\\CLEVO_KBC_INSTANCE"

bool IsSingleInstance() 
{
	// NOTE: Do not close this handle. We want to leak this as it will last the entirety of the programs lifetime.
	HANDLE hInstance = CreateEventExW(nullptr, SINGLE_INSTANCE_NAME, CREATE_EVENT_INITIAL_SET, EVENT_ALL_ACCESS);
	return !(GetLastError() == ERROR_ALREADY_EXISTS);
}
