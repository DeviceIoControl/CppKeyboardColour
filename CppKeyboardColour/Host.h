// Created by DeviceIoControl

#pragma once
#include "Zone.h"
#include "Colour.h"
#include "KeyboardType.h"
#include "IDevice.h"
#include "IHost.h"
#include "DeviceMask.h"
#include "ModelIdentifier.h"

class Host
	: public IHost
{
public:
	Host(std::shared_ptr<ModelIdentifier> pModelId, const std::vector<std::shared_ptr<IDevice>>& devices);
	~Host() override = default;

	DeviceMask GetDevices() const override;
	KeyboardType GetKeyboardType() const override;
	uint32_t GetModelID() const override;
	std::wstring GetModelName() const override;
	DeviceChannelType GetDeviceChannelType(DeviceMask device) const override;

	bool SetColour(DeviceMask devices, Zone zone, const Colour& colour) override;
	bool SetBacklightOn(DeviceMask devices) override;
	bool SetBacklightOff(DeviceMask devices) override;
	bool SendDeviceCode(DeviceMask devices, uint32_t code) override;

private:
	uint32_t m_modelId{};
	std::wstring m_modelName{};
	DeviceChannelType m_devChannelType;
	std::shared_ptr<IDevice> m_pKeyboard;
	std::shared_ptr<IDevice> m_pLightbar;
	std::shared_ptr<IDevice> m_pLogo;
};