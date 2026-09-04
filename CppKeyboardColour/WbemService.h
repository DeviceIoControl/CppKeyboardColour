// Created by DeviceIoControl

#pragma once
#include "ScopedComPtr.h"

class WbemService
{
public:
	explicit WbemService(const std::wstring& wbemNamespace = L"ROOT\\WMI");

	ScopedComPtr<IWbemClassObject> GetWbemClassObject(const std::wstring& strObjectPath);
	ScopedComPtr<IEnumWbemClassObject> GetWbemInstanceEnumerator(const std::wstring& strFilter);

	ScopedComPtr<IWbemClassObject> ExecuteMethod(
		const std::wstring& strObjectPath, 
		const std::wstring& strMethodName,
		IWbemClassObject* pInParameters);

	~WbemService();

private:
	std::wstring m_strObjectName;
	ScopedComPtr<IWbemLocator> m_pWbemLocator;
	ScopedComPtr<IWbemServices> m_pWbemServices;

	bool InitialiseCom();

	bool InitialiseComSecurity(DWORD dwAuthnLevel, DWORD dwImpLevel);

	IWbemLocator* CreateWbemLocator();

	IWbemServices* CreateNativeWbemServices(const std::wstring& strNamespace);
};
