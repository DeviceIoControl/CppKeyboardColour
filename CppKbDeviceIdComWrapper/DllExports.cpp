#include "pch.h"
#include "DllExports.h"

extern "C"
{
	HRESULT __stdcall DllCanUnloadNow()
	{
		return S_FALSE;
	}

	HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void** ppvObject)
	{
		if (!ppvObject)
		{
			return E_INVALIDARG;
		}

		if (!IsEqualCLSID(rclsid, __uuidof(CppKeyboardDeviceFactory)))
		{
			return CLASS_E_CLASSNOTAVAILABLE;
		}

		static CppKeyboardDeviceFactory s_classFactory{};

		return s_classFactory.QueryInterface(riid, ppvObject);
	}

	HRESULT WINAPI DllRegisterServer()
	{
		HKEY hAppID{};
		HKEY hClsidKey{};

		RegCreateKeyW(HKEY_CLASSES_ROOT, L"Wow6432Node\\CLSID\\{ac64eee5-64b7-40b3-9461-d1081f2ed574}\\LocalServer32", &hClsidKey);
		RegCreateKeyW(HKEY_CLASSES_ROOT, L"Wow6432Node\\AppID\\{ac64eee6-64b7-40b3-9461-d1081f2ed574}", &hAppID);

		std::wstring strDLLPath = L"";
		RegSetValueExW(hClsidKey, L"", 0, REG_SZ, reinterpret_cast<const uint8_t*>(strDLLPath.c_str()), strDLLPath.length() * sizeof(wchar_t));
		
		std::wstring strDllSurrogate = L"";
		RegSetValueExW(hAppID, L"DllSurrogate", 0, REG_SZ, reinterpret_cast<const uint8_t*>(strDllSurrogate.c_str()), strDllSurrogate.length() * sizeof(wchar_t));

		std::wstring strAppID = L"{ac64eee6-64b7-40b3-9461-d1081f2ed574}";
		RegSetValueExW(hClsidKey, L"AppID", 0, REG_SZ, reinterpret_cast<const uint8_t*>(strAppID.c_str()), strAppID.length() * sizeof(wchar_t));

		return S_FALSE;
	}

	HRESULT WINAPI DllUnRegisterServer()
	{
		return S_FALSE;
	}
}