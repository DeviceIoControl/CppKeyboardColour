#pragma once

#include "CppKeyboardDeviceFactory.h"

extern "C"
{
	HRESULT __stdcall DllCanUnloadNow();

	HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void** ppvObject);

	__declspec(dllexport) HRESULT WINAPI DllRegisterServer();

	__declspec(dllexport) HRESULT WINAPI DllUnRegisterServer();
}
