// Created by DeviceIoControl

#include "stdafx.h"
#include "Keyboard.h"
#include "DeviceIdRetriever.h"
#include "DeviceIdTranslator.h"
#include "KeyboardCommunicatorFactory.h"

Keyboard::Keyboard()
{
	DeviceIdRetriever devIdRetriever{};
	const auto deviceId = devIdRetriever.GetDeviceID();

	std::cout << "Detected Device ID: 0x" << (void*)deviceId << "\n";

	auto pDevIdTranslator = std::make_unique<DeviceIdTranslator>();
	m_kbType = pDevIdTranslator->TranslateToKBType(deviceId);

	KeyboardCommunicatorFactory kbCommFactory(std::move(pDevIdTranslator));
	m_ptrKbComms = kbCommFactory.Create(deviceId);
}

void Keyboard::SetColour(uint8_t r, uint8_t g, uint8_t b, Zone zone)
{
	Colour colour{};

	colour[INDEX_COLOUR_RED] = r;
	colour[INDEX_COLOUR_GREEN] = g;
	colour[INDEX_COLOUR_BLUE] = b;

	m_ptrKbComms->SetKBColour(zone, colour);
}

KeyboardType Keyboard::GetKBType() const
{
	return m_kbType;
};

void Keyboard::SendCode(uint32_t animation)
{
	m_ptrKbComms->SendKBCode(static_cast<uint32_t>(animation));
}

void Keyboard::SetBacklightOff()
{
	this->SetColour(0x00, 0x00, 0x00, Zone::ALL);
}

void Keyboard::SetBacklightOn()
{
	this->SetColour(0x00, 0x00, 0xFF, Zone::ALL);
}

void Keyboard::Animate(IAnimation& animation)
{
	for (size_t i = 0; i < animation.Size(); ++i)
	{
		if (const auto frame = animation.GetFrame(i))
		{
			this->SetColour(
				frame->colour[INDEX_COLOUR_RED],
				frame->colour[INDEX_COLOUR_GREEN],
				frame->colour[INDEX_COLOUR_BLUE],
				frame->zone
			);

			Sleep(frame->ms_time);
		}
	}
}

void Keyboard::PlayAnimation(IAnimation& animation, bool bShouldLoop /*= true */)
{
	if (!animation.IsSupportedKB(this->GetKBType()))
	{
		std::wcout << animation.GetName() << L" animation is not supported on this keyboard.\n";
		return;
	}

	std::wcout << L"Playing " << animation.GetName() << L" animation...\n";

	do
	{
		this->Animate(animation);

	} while (bShouldLoop);
}
