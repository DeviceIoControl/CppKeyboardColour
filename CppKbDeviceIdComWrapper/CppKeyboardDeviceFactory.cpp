#include "pch.h"

#include "CppKeyboardDevice.h"
#include "ICppKeyboardDevice.h"
#include "CppKeyboardDeviceFactory.h"

HRESULT STDMETHODCALLTYPE CppKeyboardDeviceFactory::QueryInterface(REFIID riid, void** ppvObject)
{
    if (!ppvObject)
    {
        return E_INVALIDARG;
    }

    for (auto const& currentIID : { __uuidof(IUnknown), __uuidof(IClassFactory) })
    {
        if (IsEqualIID(currentIID, riid))
        {
            AddRef();
            *ppvObject = this;
            return S_OK;
        }
    }

    return E_NOINTERFACE;
}

ULONG STDMETHODCALLTYPE CppKeyboardDeviceFactory::AddRef()
{
    return ++m_refCount;
}

ULONG STDMETHODCALLTYPE CppKeyboardDeviceFactory::Release()
{
    return --m_refCount;
}

HRESULT STDMETHODCALLTYPE CppKeyboardDeviceFactory::CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppvObject)
{
    if (!ppvObject || pUnkOuter)
    {
        return E_INVALIDARG;
    }

    for (auto const& currentIID : { __uuidof(IUnknown), __uuidof(ICppKeyboardDevice) })
    {
        if (IsEqualIID(currentIID, riid))
        {
            // TODO: Create a global active object count - Required for DllCanUnloadNow.
            *ppvObject = new CppKeyboardDevice();
            return S_OK;
        }
    }

    return S_OK;
}

HRESULT STDMETHODCALLTYPE CppKeyboardDeviceFactory::LockServer(BOOL fLock)
{
    auto const refCount = (fLock ? this->AddRef() : this->Release());
    return S_OK;
}
