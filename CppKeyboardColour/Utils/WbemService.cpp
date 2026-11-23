// Created by DeviceIoControl

#include "stdafx.h"
#include "WbemService.h"
#include "../Console/Logger.h"

WbemService::WbemService(const std::wstring& wbemNamespace /* = L"ROOT\\WMI" */)
{
	m_comInit.InitialiseSecurity(RPC_C_AUTHN_LEVEL_CONNECT, RPC_C_IMP_LEVEL_IMPERSONATE);

	m_pWbemLocator.Reset(this->CreateWbemLocator());
	m_pWbemServices.Reset(this->CreateNativeWbemServices(wbemNamespace));

	if (!m_pWbemLocator || !m_pWbemServices)
	{
		KB_SET_FATAL_ERROR(ERROR_API_UNAVAILABLE);
		KB_FATAL(L"Failed to initialize WMI.");
	}
}

ScopedComPtr<IWbemClassObject> WbemService::GetWbemClassObject(const std::wstring& strObjectPath)
{
	IWbemClassObject* pWbemClassObject = nullptr;
	const auto hr = m_pWbemServices->GetObjectW((BSTR)strObjectPath.c_str(), NULL, nullptr, &pWbemClassObject, nullptr);
	
	if (FAILED(hr))
	{
		KB_ERROR_STATUS(L"IWbemServices::GetObjectW", hr);
	}

	return ScopedComPtr<IWbemClassObject>(pWbemClassObject);
}

ScopedComPtr<IEnumWbemClassObject> WbemService::GetWbemInstanceEnumerator(const std::wstring& strFilter) 
{
	IEnumWbemClassObject* pWbemClassEnum = nullptr;
	const auto hr = m_pWbemServices->CreateInstanceEnum((BSTR)strFilter.c_str(), WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, nullptr, &pWbemClassEnum);

	if (FAILED(hr))
	{
		KB_ERROR_STATUS(L"IWbemServices::CreateInstanceEnum", hr);
	}

	return ScopedComPtr<IEnumWbemClassObject>(pWbemClassEnum);
}

ScopedComPtr<IWbemClassObject> WbemService::ExecuteMethod(const std::wstring& strObjectPath, const std::wstring& strMethodName,
	IWbemClassObject* pInParameters)
{
	IWbemClassObject* pOutParams = nullptr;

	const auto hr = m_pWbemServices->ExecMethod((BSTR)strObjectPath.c_str(), 
		(BSTR)strMethodName.c_str(), NULL, nullptr, pInParameters, &pOutParams, nullptr);

	if (FAILED(hr))
	{
		KB_ERROR_STATUS(L"IWbemServices::ExecMethod", hr);
	}

	return ScopedComPtr<IWbemClassObject>(pOutParams);
}

IWbemLocator* WbemService::CreateWbemLocator()
{
	IWbemLocator* pWbemLocator = nullptr;

	const auto hError = CoCreateInstance(__uuidof(WbemLocator), nullptr,
		CLSCTX_INPROC_SERVER, IID_IWbemLocator, (void**)&pWbemLocator);

	if (FAILED(hError))
	{
		KB_ERROR_STATUS(L"CoCreateInstance", hError);
	}

	return SUCCEEDED(hError) ? pWbemLocator : nullptr;
}

IWbemServices* WbemService::CreateNativeWbemServices(const std::wstring& strNamespace)
{
	IWbemServices* pWbemServices = nullptr;

	const auto hError = m_pWbemLocator->ConnectServer(
		(BSTR)strNamespace.c_str(), nullptr, nullptr, nullptr, NULL, nullptr, nullptr, &pWbemServices
	);

	if (FAILED(hError))
	{
		KB_ERROR_STATUS(L"IWbemLocation::ConnectServer", hError);
	}

	return SUCCEEDED(hError) ? pWbemServices : nullptr;
}
