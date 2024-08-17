#pragma once

class __declspec(uuid("ac64eee5-64b7-40b3-9461-d1081f2ed574")) CppKeyboardDeviceFactory
	: public IClassFactory
{
public:
	CppKeyboardDeviceFactory() = default;
	~CppKeyboardDeviceFactory() = default;

	ULONG GetRefCount() { return m_refCount; }

	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppvObject) override;

	ULONG STDMETHODCALLTYPE AddRef() override;

	ULONG STDMETHODCALLTYPE Release() override;

	HRESULT STDMETHODCALLTYPE CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppvObject) override;

	HRESULT STDMETHODCALLTYPE LockServer(BOOL fLock) override;

private:
	std::atomic<uint32_t> m_refCount = 1;
};