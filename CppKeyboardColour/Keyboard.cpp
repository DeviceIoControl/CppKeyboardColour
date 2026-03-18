// Created by DeviceIoControl

#include "stdafx.h"
#include "Keyboard.h"

using millisec = std::chrono::milliseconds;

Keyboard::Keyboard(KeyboardType kbType, IKeyboardCommunicatorPtr ptrKbComms)
	: m_kbType(kbType),
	m_ptrKbComms(std::move(ptrKbComms))
{
}

void Keyboard::SetColour(uint8_t r, uint8_t g, uint8_t b, Zone zone)
{
	m_ptrKbComms->SetKBColour(zone, m_colourFactory.Create(r, g, b));
}

KeyboardType Keyboard::GetKBType() const
{
	return m_kbType;
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

			std::this_thread::sleep_for(millisec(frame->ms_time));
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
