#pragma once

#include "ICppKeyboardDevice.h"

class CppKeyboardDevice 
	: public ICppKeyboardDevice
{
public:
    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppvObject) override;

    ULONG STDMETHODCALLTYPE AddRef() override;

    ULONG STDMETHODCALLTYPE Release() override;

    HRESULT GetDeviceID(uint32_t* puiDeviceId) const override;

private:
    std::atomic<uint32_t> m_refCount = 1;
};