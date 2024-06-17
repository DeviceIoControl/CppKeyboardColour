#pragma once

#include "stdafx.h"
#include "DeviceIds.h"
#include "IKeyboardCommunicator.h"

#include "WmiKBCommunicator.h"
#include "InsydeKBCommunicator.h"

class KeyboardCommunicatorFactory 
{
public:
	KeyboardCommunicatorFactory() 
	{
		m_kbCommunicatorMap[DEVICE_ID_P650RS_G] = std::make_shared<WmiKBCommunicator>();
		m_kbCommunicatorMap[DEVICE_ID_NP50SXX] = std::make_shared<InsydeKBCommunicator>();
	}

	IKeyboardCommunicatorPtr Create(uint32_t deviceId) 
	{
		auto kbCommIterator = m_kbCommunicatorMap.find(deviceId);

		if (kbCommIterator != m_kbCommunicatorMap.cend()) 
		{
			return kbCommIterator->second;
		}

		return nullptr;
	}
	
	~KeyboardCommunicatorFactory() = default;

private:
	std::unordered_map<uint32_t, IKeyboardCommunicatorPtr> m_kbCommunicatorMap;
};