// Created by DeviceIoControl

#pragma once
#include "KeyboardType.h"
#include "DeviceChannelType.h"
#include "DeviceMask.h"
#include "IModelIdRetriever.h"
#include "HostDeviceProperties.h"

class ModelIdentifier
{
public:
	explicit ModelIdentifier(std::unique_ptr<IModelIdRetriever> pModelRetriever);
	explicit ModelIdentifier(bool useLegacyModelIdRetriever = false, bool useDebugModel = false);

	uint32_t GetModelID() const;
	KeyboardType GetKeyboardType() const;
	DeviceChannelType GetDeviceChannelType() const;
	DeviceMask GetHostDevices() const;
	std::wstring GetModelName() const;

	~ModelIdentifier() = default;

private:
	uint32_t m_modelId = 0;
	std::map<uint32_t, HOST_DEVICE_PROPS> m_modelIdToDevProps{};

	void InitializeSingleZoneKBs();
	void InitializeTripleZoneKBs();
	void InitializeTripleZoneKBsWithPeripherals();

	std::wstring_view ConvertModelIdToString(uint32_t modelId);
};