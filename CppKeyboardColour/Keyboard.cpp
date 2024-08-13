// Created by DeviceIoControl

#include "stdafx.h"
#include "Keyboard.h"
#include "DeviceIdRetriever.h"
#include "DeviceIdTranslator.h"
#include "KeyboardCommunicatorFactory.h"

Keyboard::Keyboard()
{
	DeviceIdRetriever devIdRetriever{};
	DeviceIdTranslator devIdTranslator{};
	KeyboardCommunicatorFactory kbCommFactory{};

	const auto deviceId = devIdRetriever.GetDeviceID();

	m_kbType = devIdTranslator.TranslateToKBType(deviceId);
	m_ptrKbComms = kbCommFactory.Create(deviceId);
}

void Keyboard::SetColour(uint8_t r, uint8_t g, uint8_t b, Zone zone)
{
	Colour colour{};

	colour[INDEX_COLOUR_RED] = r;
	colour[INDEX_COLOUR_GREEN] = g;
	colour[INDEX_COLOUR_BLUE] = b;

	m_ptrKbComms->SetKeyboardColour(zone, colour);
}

KeyboardType Keyboard::GetKBType() const
{
	return m_kbType;
};

void Keyboard::SysAnimation(SystemAnimation animation)
{
	switch (animation)
	{
	case SystemAnimation::KB_MODE_OFF:
		return this->SetColour(0x00, 0x00, 0x00, Zone::ALL);

	case SystemAnimation::KB_MODE_STANDARD:
		return this->SetColour(0x00, 0x00, 0xFF, Zone::ALL);
	}

	m_ptrKbComms->SendKeyboardData(static_cast<uint32_t>(animation));
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

void Keyboard::PlayAnimation(IAnimation& animation, bool bShouldLoop /*= true*/)
{
	if (animation.IsSupportedKB(this->GetKBType()))
	{
		do
		{
			this->Animate(animation);

		} while (bShouldLoop);
	}
}
