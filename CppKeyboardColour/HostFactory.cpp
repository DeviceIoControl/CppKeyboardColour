// Created by DeviceIoControl

#include "stdafx.h"
#include "HostFactory.h"
#include "ModelIds.h"
#include "DeviceChannelFactory.h"

namespace 
{
	std::ostream& operator<<(std::ostream& _Ostr, DeviceMask devices) 
	{
		if (!!(devices & DeviceMask::Keyboard)) 
		{
			_Ostr << "[Keyboard] ";
		}

		if (!!(devices & DeviceMask::Lightbar))
		{
			_Ostr << "[Lightbar] ";
		}

		if (!!(devices & DeviceMask::Logo))
		{
			_Ostr << "[Logo] ";
		}

		return _Ostr;
	}

	std::ostream& operator<<(std::ostream& _Ostr, KeyboardType kbType) 
	{
		switch (kbType) 
		{
		case KeyboardType::FAKE:
			return _Ostr << "Fake";

		case KeyboardType::SINGLE_ZONE:
			return _Ostr << "Single Zone";

		case KeyboardType::TRIPLE_ZONE:
			return _Ostr << "Triple Zone";

		case KeyboardType::PER_KEY:
			return _Ostr << "Per-Key";
		}

		return _Ostr;
	}

} // namespace

HostFactory::HostFactory(std::unique_ptr<ModelIdRetriever> pModelIdRetriever)
	: m_modelIdRetriever(std::move(pModelIdRetriever))
{
	this->InitializeHostDeviceProperties();
	this->InitializeDeviceFactory();
}

HostFactory::HostFactory()
	: HostFactory(std::make_unique<ModelIdRetriever>())
{
}

std::unique_ptr<Host> HostFactory::Create()
{
	auto const hostDevices = this->GetHostDevices(m_modelId);

	std::cout << "Detected Model ID: 0x" << (void*)m_modelId << "\n";
	std::cout << "Host Devices: " << hostDevices << "\n\n";

	if (!!(hostDevices & DeviceMask::Keyboard))
	{
		std::cout << "Keyboard Type: " << this->GetKeyboardType(m_modelId) << "\n";
	}

	auto const devices = this->CreateRequiredDevices(hostDevices);
	return std::make_unique<Host>(m_modelId, devices);
}

void HostFactory::InitializeHostDeviceProperties()
{
	this->InitializeSingleZoneKBs();
	this->InitializeTripleZoneKBs();
	this->InitializeTripleZoneKBsWithPeripherals();
}

bool HostFactory::InitializeDeviceFactory()
{
	DeviceChannelFactory devChannelFactory{};

	m_modelId = m_modelIdRetriever->GetModelID();
	m_devFactory = std::make_unique<DeviceFactory>(devChannelFactory.Create(this->GetDeviceChannelType(m_modelId)));

	return (m_modelId && m_devFactory);
}

std::vector<std::shared_ptr<IDevice>> HostFactory::CreateRequiredDevices(DeviceMask deviceTypes)
{
	std::vector<std::shared_ptr<IDevice>> devices{};

	if (!!(deviceTypes & DeviceMask::Keyboard))
	{
		auto const keyboardType = this->GetKeyboardType(m_modelId);
		devices.emplace_back(m_devFactory->CreateKeyboard(keyboardType));
	}

	if (!!(deviceTypes & DeviceMask::Lightbar))
	{
		devices.emplace_back(m_devFactory->CreateLightbar());
	}

	if (!!(deviceTypes & DeviceMask::Logo))
	{
		devices.emplace_back(m_devFactory->CreateLogo());
	}

	return devices;
}

KeyboardType HostFactory::GetKeyboardType(uint32_t modelId) const
{
	auto const result = m_modelIdToDevProps.find(modelId);
	return (result != m_modelIdToDevProps.cend()) ? result->second.kbType : KeyboardType::NONE;
}

DeviceChannelType HostFactory::GetDeviceChannelType(uint32_t modelId) const
{
	auto const result = m_modelIdToDevProps.find(modelId);
	return (result != m_modelIdToDevProps.cend()) ? result->second.deviceChannelType : DeviceChannelType::None;
}

DeviceMask HostFactory::GetHostDevices(uint32_t modelId) const
{
	auto const result = m_modelIdToDevProps.find(modelId);
	return (result != m_modelIdToDevProps.cend()) ? result->second.devices : DeviceMask::Unknown;
}

void HostFactory::InitializeSingleZoneKBs()
{
	std::array<uint32_t, 9> constexpr SINGLE_ZONE_INSYDE_MODEL_IDS
	{
		MODEL_ID_NP50RXX, MODEL_ID_NH70XX, MODEL_ID_NKNP50XX,
		MODEL_ID_PC50DXX, MODEL_ID_A715XX, MODEL_ID_NP50SXX,
		MODEL_ID_CV15XX, MODEL_ID_NP60SXX, MODEL_ID_V360EXX
		//, MODEL_ID_NH77XX
	};

	for (auto const currentModelId : SINGLE_ZONE_INSYDE_MODEL_IDS)
	{
		m_modelIdToDevProps[currentModelId].devices = DeviceMask::Keyboard;
		m_modelIdToDevProps[currentModelId].kbType = KeyboardType::SINGLE_ZONE;
		m_modelIdToDevProps[currentModelId].deviceChannelType = DeviceChannelType::Insyde;
	}
}

void HostFactory::InitializeTripleZoneKBs()
{
	m_modelIdToDevProps[MODEL_ID_P650RS_G].devices = DeviceMask::Keyboard;
	m_modelIdToDevProps[MODEL_ID_P650RS_G].kbType = KeyboardType::TRIPLE_ZONE;
	m_modelIdToDevProps[MODEL_ID_P650RS_G].deviceChannelType = DeviceChannelType::Wmi;
}

void HostFactory::InitializeTripleZoneKBsWithPeripherals()
{
	m_modelIdToDevProps[MODEL_ID_FAKE].devices = DeviceMask::Keyboard | DeviceMask::Lightbar | DeviceMask::Logo;
	m_modelIdToDevProps[MODEL_ID_FAKE].kbType = KeyboardType::TRIPLE_ZONE;
	m_modelIdToDevProps[MODEL_ID_FAKE].deviceChannelType = DeviceChannelType::Fake;
}