#pragma once

#include "stdafx.h"

class NamedPipe
{
public:
	NamedPipe(const std::wstring& strPipeName, uint32_t uiBufferLength) 
		: m_dwMessageLength(uiBufferLength)
	{
		m_hPipe = CreatePipeInternal(strPipeName, uiBufferLength, 4);
	}
	
	bool Write(const uint8_t* pData, uint32_t uiBytes)
	{
		DWORD dwBytesWritten = NULL;
		return WriteFile(m_hPipe, pData, uiBytes, &dwBytesWritten, nullptr);
	}

	bool Read(uint8_t* pData, uint32_t uiBytes)
	{
		DWORD dwBytesRead = NULL;
		return ReadFile(m_hPipe, pData, uiBytes, &dwBytesRead, nullptr);
	}

	DWORD MessageLength() const { return m_dwMessageLength; }

	~NamedPipe()
	{
		CloseHandle(m_hPipe);
	}

private:
	HANDLE m_hPipe = nullptr;
	DWORD m_dwMessageLength = NULL;

	HANDLE CreatePipeInternal(const std::wstring& strPipeName, uint32_t uiBufferLength, uint16_t maxInstances)
	{
		CreateNamedPipeW(strPipeName.c_str(), PIPE_ACCESS_DUPLEX | FILE_FLAG_FIRST_PIPE_INSTANCE,
			PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT | PIPE_REJECT_REMOTE_CLIENTS, maxInstances,
			uiBufferLength, uiBufferLength, NMPWAIT_USE_DEFAULT_WAIT, nullptr);
	}
};