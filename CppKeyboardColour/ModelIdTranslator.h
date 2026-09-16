// Created by DeviceIoControl

#pragma once
#include "KeyboardType.h"
#include "DeviceChannelType.h"
#include "DeviceMask.h"
#include "IModelIdRetriever.h"

struct HOST_DEVICE_PROPS
{
	KeyboardType kbType;
	DeviceMask devices;
	DeviceChannelType deviceChannelType;
	std::wstring modelName;
};

class ModelIdTranslator 
{
public:
	ModelIdTranslator(std::unique_ptr<IModelIdRetriever> pModelRetriever);
	~ModelIdTranslator() = default;

	KeyboardType GetKeyboardType() const;
	DeviceChannelType GetDeviceChannelType() const;
	DeviceMask GetHostDevices() const;
	std::wstring GetModelName() const;

private:
	uint32_t m_modelId = 0;
	std::map<uint32_t, HOST_DEVICE_PROPS> m_modelIdToDevProps{};

	void InitializeSingleZoneKBs();
	void InitializeTripleZoneKBs();
	void InitializeTripleZoneKBsWithPeripherals();

	std::wstring ConvertModelIdToString(uint32_t modelId);
};