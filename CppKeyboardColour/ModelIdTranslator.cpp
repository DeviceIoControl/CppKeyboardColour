// Created by DeviceIoControl

#include "stdafx.h"
#include "ModelIdTranslator.h"
#include "ModelIds.h"

ModelIdTranslator::ModelIdTranslator()
{
	this->InitializeSingleZoneKBs();
	this->InitializeTripleZoneKBs();
	this->InitializeTripleZoneKBsWithPeripherals();
}

KeyboardType ModelIdTranslator::GetKeyboardType(uint32_t modelId) const
{
	const auto result = m_modelIdToDevProps.find(modelId);
	return (result != m_modelIdToDevProps.cend()) ? result->second.kbType : KeyboardType::NONE;
}

DeviceChannelType ModelIdTranslator::GetDeviceChannelType(uint32_t modelId) const
{
	const auto result = m_modelIdToDevProps.find(modelId);
	return (result != m_modelIdToDevProps.cend()) ? result->second.deviceChannelType : DeviceChannelType::None;
}

DeviceMask ModelIdTranslator::GetHostDevices(uint32_t modelId) const
{
	const auto result = m_modelIdToDevProps.find(modelId);
	return (result != m_modelIdToDevProps.cend()) ? result->second.devices : DeviceMask::Unknown;
}

void ModelIdTranslator::InitializeSingleZoneKBs()
{
	std::array constexpr SINGLE_ZONE_INSYDE_MODEL_IDS
	{
		MODEL_ID_NP50RXX, MODEL_ID_NH70XX, MODEL_ID_NKNP50XX,
		MODEL_ID_PC50DXX, MODEL_ID_A715XX, MODEL_ID_NP50SXX,
		MODEL_ID_CV15XX, MODEL_ID_NP60SXX, MODEL_ID_V360EXX
		//, MODEL_ID_NH77XX
	};

	for (const auto currentModelId : SINGLE_ZONE_INSYDE_MODEL_IDS)
	{
		m_modelIdToDevProps[currentModelId].devices = DeviceMask::Keyboard;
		m_modelIdToDevProps[currentModelId].kbType = KeyboardType::SINGLE_ZONE;
		m_modelIdToDevProps[currentModelId].deviceChannelType = DeviceChannelType::Insyde;
	}
}

void ModelIdTranslator::InitializeTripleZoneKBs()
{
	for (const auto currentModelId : { MODEL_ID_P650RS_G })
	{
		m_modelIdToDevProps[currentModelId].devices = DeviceMask::Keyboard;
		m_modelIdToDevProps[currentModelId].kbType = KeyboardType::TRIPLE_ZONE;
		m_modelIdToDevProps[currentModelId].deviceChannelType = DeviceChannelType::Wmi;
	}
}

void ModelIdTranslator::InitializeTripleZoneKBsWithPeripherals()
{
	m_modelIdToDevProps[MODEL_ID_DEBUG].devices = DeviceMask::Keyboard | DeviceMask::Lightbar | DeviceMask::Logo;
	m_modelIdToDevProps[MODEL_ID_DEBUG].kbType = KeyboardType::TRIPLE_ZONE;
	m_modelIdToDevProps[MODEL_ID_DEBUG].deviceChannelType = DeviceChannelType::Debug;
}
