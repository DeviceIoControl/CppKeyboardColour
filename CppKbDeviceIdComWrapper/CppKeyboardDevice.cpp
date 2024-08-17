
#include "pch.h"
#include "CppKeyboardDevice.h"

HRESULT STDMETHODCALLTYPE CppKeyboardDevice::QueryInterface(REFIID riid, void** ppvObject)
{
    if (!ppvObject)
    {
        return E_INVALIDARG;
    }

    for (auto const& currentIID : { __uuidof(IUnknown), __uuidof(ICppKeyboardDevice) })
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

ULONG STDMETHODCALLTYPE CppKeyboardDevice::AddRef()
{
    return ++m_refCount;
}

ULONG STDMETHODCALLTYPE CppKeyboardDevice::Release()
{
    return --m_refCount;
}

HRESULT CppKeyboardDevice::GetDeviceID(uint32_t* puiDeviceId) const
{
    // Load GetProductInfo.dll.
    return E_NOTIMPL;
}