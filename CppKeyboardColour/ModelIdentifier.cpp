// Created by DeviceIoControl

#include "stdafx.h"
#include "ModelIdentifier.h"
#include "ModelIds.h"
#include "ModelIdRetriever.h"
#include "LegacyModelIdRetriever.h"

namespace
{
	std::array constexpr g_SingleZoneInsydeModelIds
	{
		MODEL_ID_NP50RXX, MODEL_ID_NH70XX, MODEL_ID_NKNP50XX,
		MODEL_ID_PC50DXX, MODEL_ID_A715XX, MODEL_ID_NP50SXX,
		MODEL_ID_CV15XX, MODEL_ID_NP60SXX, MODEL_ID_V360EXX
		//, MODEL_ID_NH77XX
	};

	template<typename TModelIdRetriever>
	std::unique_ptr<IModelIdRetriever> CreateModelIdRetriever(bool useDebugModel) 
	{
		return std::make_unique<TModelIdRetriever>(useDebugModel);
	}
} // namespace 

ModelIdentifier::ModelIdentifier(std::unique_ptr<IModelIdRetriever> pModelRetriever)
{
	this->InitializeSingleZoneKBs();
	this->InitializeTripleZoneKBs();
	this->InitializeTripleZoneKBsWithPeripherals();

	m_modelId = pModelRetriever->GetModelID();
}

ModelIdentifier::ModelIdentifier(bool useLegacyModelIdRetriever /*= false*/, bool useDebugModel /*= false*/)
	: ModelIdentifier(useLegacyModelIdRetriever ? CreateModelIdRetriever<LegacyModelIdRetriever>(useDebugModel) : CreateModelIdRetriever<ModelIdRetriever>(useDebugModel))
{
}

uint32_t ModelIdentifier::GetModelID() const
{
	return m_modelId;
}

KeyboardType ModelIdentifier::GetKeyboardType() const
{
	const auto result = m_modelIdToDevProps.find(m_modelId);
	return (result != m_modelIdToDevProps.cend()) ? result->second.kbType : KeyboardType::NONE;
}

DeviceChannelType ModelIdentifier::GetDeviceChannelType() const
{
	const auto result = m_modelIdToDevProps.find(m_modelId);
	return (result != m_modelIdToDevProps.cend()) ? result->second.deviceChannelType : DeviceChannelType::None;
}

DeviceMask ModelIdentifier::GetHostDevices() const
{
	const auto result = m_modelIdToDevProps.find(m_modelId);
	return (result != m_modelIdToDevProps.cend()) ? result->second.devices : DeviceMask::Unknown;
}

std::wstring ModelIdentifier::GetModelName() const
{
	const auto result = m_modelIdToDevProps.find(m_modelId);
	return (result != m_modelIdToDevProps.cend()) ? result->second.modelName : std::wstring{L"N/A"};
}

void ModelIdentifier::InitializeSingleZoneKBs()
{
	for (const auto currentModelId : g_SingleZoneInsydeModelIds)
	{
		m_modelIdToDevProps[currentModelId].devices = DeviceMask::Keyboard;
		m_modelIdToDevProps[currentModelId].kbType = KeyboardType::SINGLE_ZONE;
		m_modelIdToDevProps[currentModelId].deviceChannelType = DeviceChannelType::Insyde;
		m_modelIdToDevProps[currentModelId].modelName = ConvertModelIdToString(currentModelId);
	}
}

void ModelIdentifier::InitializeTripleZoneKBs()
{
	for (const auto currentModelId : { MODEL_ID_P650RS_GH, MODEL_ID_P650RS_GD })
	{
		m_modelIdToDevProps[currentModelId].devices = DeviceMask::Keyboard;
		m_modelIdToDevProps[currentModelId].kbType = KeyboardType::TRIPLE_ZONE;
		m_modelIdToDevProps[currentModelId].deviceChannelType = DeviceChannelType::Wmi;
		m_modelIdToDevProps[currentModelId].modelName = ConvertModelIdToString(currentModelId);
	}
}

void ModelIdentifier::InitializeTripleZoneKBsWithPeripherals()
{
	m_modelIdToDevProps[MODEL_ID_DEBUG].devices = DeviceMask::Keyboard | DeviceMask::Lightbar | DeviceMask::Logo;
	m_modelIdToDevProps[MODEL_ID_DEBUG].kbType = KeyboardType::TRIPLE_ZONE;
	m_modelIdToDevProps[MODEL_ID_DEBUG].deviceChannelType = DeviceChannelType::Debug;
	m_modelIdToDevProps[MODEL_ID_DEBUG].modelName = ConvertModelIdToString(MODEL_ID_DEBUG);
}

std::wstring_view ModelIdentifier::ConvertModelIdToString(uint32_t modelId)
{
	switch (modelId) 
	{
	case MODEL_ID_NP50RXX:
		return L"CLEVO NP50RXX Series";

	case MODEL_ID_NH70XX:
		return L"CLEVO NH70XX Series";

	case MODEL_ID_NKNP50XX:
		return L"CLEVO NKNP50XX Series";

	case MODEL_ID_PC50DXX:
		return L"CLEVO PC50DXX Series";

	case MODEL_ID_A715XX:
		return L"CLEVO A715XX Series";

	case MODEL_ID_NP50SXX:
		return L"CLEVO NP50SXX Series";

	case MODEL_ID_CV15XX:
		return L"CLEVO CV15XX Series";

	case MODEL_ID_NP60SXX:
		return L"CLEVO NP60SXX Series";

	case MODEL_ID_V360EXX:
		return L"CLEVO V360EXX Series";

	case MODEL_ID_P650RS_GH:
	case MODEL_ID_P650RS_GD:
		return L"CLEVO P650RS-G Series";

	case MODEL_ID_DEBUG:
		return L"CLEVO XXXXXX Series";
	}
}