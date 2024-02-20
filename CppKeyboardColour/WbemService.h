#pragma once

#include "stdafx.h"
#include "ScopedComPtr.h"

namespace WMI 
{
	class WbemService
	{
	public:
		WbemService(const std::wstring& wbemNamespace)
		{
			InitialiseCom();
			InitialiseComSecurity(RPC_C_AUTHN_LEVEL_CONNECT, RPC_C_IMP_LEVEL_IMPERSONATE);
			
			m_pWbemLocator.Reset(this->CreateWbemLocator());
			m_pWbemServices.Reset(this->CreateNativeWbemServices(wbemNamespace));
		}

		ScopedComPtr<IWbemClassObject> GetWbemClassObject(const std::wstring& strObjectPath)
		{
			IWbemClassObject* pWbemClassObject = nullptr;
			m_pWbemServices->GetObjectW((BSTR)strObjectPath.c_str(), NULL, nullptr, &pWbemClassObject, nullptr);

			return ScopedComPtr<IWbemClassObject>(pWbemClassObject);
		}

		ScopedComPtr<IWbemClassObject> ExecuteMethod(const std::wstring& strObjectPath, const std::wstring& strMethodName,
			IWbemClassObject* pInParameters)
		{
			IWbemClassObject* pOutParams = nullptr;

			m_pWbemServices->ExecMethod((BSTR)strObjectPath.c_str(), (BSTR)strMethodName.c_str(), NULL, nullptr, pInParameters,
				&pOutParams, nullptr);

			return ScopedComPtr<IWbemClassObject>(pOutParams);
		}

		~WbemService()
		{
			CoUninitialize();
		}

	private:
		std::wstring m_strObjectName;
		ScopedComPtr<IWbemLocator> m_pWbemLocator;
		ScopedComPtr<IWbemServices> m_pWbemServices;

		bool InitialiseCom()
		{
			const auto hError = CoInitializeEx(nullptr, COINIT::COINIT_APARTMENTTHREADED);
			return SUCCEEDED(hError);
		}

		bool InitialiseComSecurity(DWORD dwAuthnLevel, DWORD dwImpLevel) 
		{
			const auto hError = CoInitializeSecurity(
				nullptr,
				-1,
				nullptr,
				nullptr,
				dwAuthnLevel,
				dwImpLevel,
				nullptr,
				EOAC_NONE,
				nullptr);

			return SUCCEEDED(hError);
		}

		IWbemLocator* CreateWbemLocator()
		{
			IWbemLocator* pWbemLocator = nullptr;

			const auto hError = CoCreateInstance(__uuidof(WbemLocator), nullptr, 
				CLSCTX_INPROC_SERVER, IID_IWbemLocator, (void**)&pWbemLocator);

			return pWbemLocator;
		}
		
		IWbemServices* CreateNativeWbemServices(const std::wstring& strNamespace) 
		{
			IWbemServices* pWbemServices = nullptr;

			const auto hError = m_pWbemLocator->ConnectServer(
				(BSTR)strNamespace.c_str(), nullptr, nullptr, nullptr, NULL, nullptr, nullptr, &pWbemServices
			);

			return pWbemServices;
		}
	};
	
	WbemService* Get(std::wstring strNamespace = L"ROOT\\WMI")
	{
		// We use the Apartment threaded model in COM, therefore everything is thread local. 
		// thus this pointer is only really valid on the thread it was initialised on.
		static thread_local std::unique_ptr<WbemService> s_WmiService = std::make_unique<WbemService>(strNamespace);
		return s_WmiService.get();
	}

} // namespace WMI