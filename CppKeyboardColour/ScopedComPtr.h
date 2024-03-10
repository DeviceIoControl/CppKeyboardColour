#pragma once

#include "stdafx.h"

template<typename T>
class ScopedComPtr 
{
public:
	ScopedComPtr() = default;

	explicit ScopedComPtr(IUnknown* pInterface, bool bAddRef)
		: m_ptr(pInterface)
	{
		if (bAddRef) 
		{
			DoAddRef(m_ptr);
		}
	}

	explicit ScopedComPtr(IUnknown* pInterface) 
		: ScopedComPtr(pInterface, false)
	{
	}

	ScopedComPtr(const ScopedComPtr&) = delete;
	ScopedComPtr& operator=(const ScopedComPtr&) = delete;

	ScopedComPtr(ScopedComPtr&& that) noexcept
	{
		std::swap(this->m_ptr, that.m_ptr);
	}
	
	ScopedComPtr& operator=(ScopedComPtr&& rhs) noexcept
	{
		std::swap(this->m_ptr, rhs.m_ptr);
		return *this;
	}

	inline T* Get() const 
	{
		DoAddRef(m_ptr);
		return reinterpret_cast<T*>(m_ptr); 
	}

	inline T* Reset(T* ptr)
	{
		auto pTemp = m_ptr;

		DoRelease(m_ptr);
		DoAddRef(ptr);

		m_ptr = reinterpret_cast<IUnknown*>(ptr);

		return reinterpret_cast<T*>(pTemp);
	}

	inline bool IsValid() const { return !!(m_ptr); }

	inline T* operator->() const { return reinterpret_cast<T*>(m_ptr); }

	~ScopedComPtr()
	{
		this->DoRelease(m_ptr);
	}

private:
	IUnknown* m_ptr = nullptr;

	ULONG DoAddRef(IUnknown* pUnk) const
	{
		return pUnk ? pUnk->AddRef() : 0;
	}

	ULONG DoRelease(IUnknown* pUnk) const 
	{
		return pUnk ? pUnk->Release() : 0;
	}
};