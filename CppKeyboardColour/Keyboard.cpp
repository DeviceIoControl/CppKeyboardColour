// Created by DeviceIoControl

#include "stdafx.h"
#include "Keyboard.h"

using millisec = std::chrono::milliseconds;

Keyboard::Keyboard(std::shared_ptr<IKeyboardDevice> pKBDevice, std::shared_ptr<IKeyboardCommunicator> pKbComms)
	: m_pKBDevice(std::move(pKBDevice)),
	m_ptrKbComms(std::move(pKbComms))
{
}

void Keyboard::SetColour(uint8_t r, uint8_t g, uint8_t b, Zone zone)
{
	m_ptrKbComms->SetKBColour(zone, m_colourFactory.Create(r, g, b));
}

KeyboardType Keyboard::GetKBType() const
{
	return m_pKBDevice->GetKeyboardType();
};

void Keyboard::SendCode(uint32_t code)
{
	m_ptrKbComms->SendKBCode(code);
}

void Keyboard::SetBacklightOff()
{
	this->SetColour(0x00, 0x00, 0x00, Zone::ALL);
}

void Keyboard::SetBacklightOn()
{
	this->SetColour(0x00, 0x00, 0xFF, Zone::ALL);
}

bool Keyboard::SetSpeedFactor(float factor)
{
	if ((factor >= 0.01f) && (factor <= 2.5f))
	{
		m_speedFactor = factor;
		return true;
	}

	return false;
}

void Keyboard::Animate(IAnimation& animation)
{
	for (size_t i = 0; i < animation.Size(); ++i)
	{
		if (const auto frame = animation.GetFrame(i))
		{
			m_ptrKbComms->SetKBColour(frame->zone, frame->colour);
			auto const frameSleep = static_cast<uint32_t>(frame->ms_time / m_speedFactor);
			std::this_thread::sleep_for(millisec(frameSleep));
		}
	}
}

void Keyboard::PlayAnimation(IAnimation& animation, bool bShouldLoop)
{
	if (!animation.IsSupportedKB(this->GetKBType()))
	{
		std::wcout << animation.GetName() << L" animation is not supported on this system.\n";
		return;
	}

	std::wcout << L"Playing " << animation.GetName() << L" animation...\n";

	do
	{
		this->Animate(animation);

	} while (bShouldLoop);
}
