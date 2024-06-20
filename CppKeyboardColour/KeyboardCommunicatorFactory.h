// Created by DeviceIoControl

#pragma once

#include "stdafx.h"
#include "DeviceIds.h"
#include "IKeyboardCommunicator.h"

#include "WmiKBCommunicator.h"
#include "InsydeKBCommunicator.h"
#include "FakeKeyboardCommunicator.h"

#define KB_COMM_INDEX_FAKE 0
#define KB_COMM_INDEX_WMI 1
#define KB_COMM_INDEX_INSYDE 2

class KeyboardCommunicatorFactory 
{
public:
	KeyboardCommunicatorFactory() 
	{
		this->CreateKBCommunicators();
		
		m_deviceToKbCommMap[DEVICE_ID_FAKE] = m_kbComms[KB_COMM_INDEX_FAKE];
		m_deviceToKbCommMap[DEVICE_ID_P650RS_G] = m_kbComms[KB_COMM_INDEX_WMI];
		m_deviceToKbCommMap[DEVICE_ID_NP50SXX] = m_kbComms[KB_COMM_INDEX_INSYDE];
	}

	IKeyboardCommunicatorPtr Create(uint32_t deviceId)
	{
		const auto kbCommIterator = m_deviceToKbCommMap.find(deviceId);

		if (kbCommIterator != m_deviceToKbCommMap.cend())
		{
			return kbCommIterator->second;
		}

		return nullptr;
	}
	
	~KeyboardCommunicatorFactory() = default;

private:
	std::array<IKeyboardCommunicatorPtr, 3> m_kbComms{};
	std::unordered_map<uint32_t, IKeyboardCommunicatorPtr> m_deviceToKbCommMap{};

	void CreateKBCommunicators()
	{
		m_kbComms[KB_COMM_INDEX_WMI] = std::make_shared<WmiKBCommunicator>();
		m_kbComms[KB_COMM_INDEX_INSYDE] = std::make_shared<InsydeKBCommunicator>();
		m_kbComms[KB_COMM_INDEX_FAKE] = std::make_shared<FakeKeyboardCommunicator>();
	}
};