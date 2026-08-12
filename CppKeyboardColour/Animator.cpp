// Created by DeviceIoControl

#include "stdafx.h"
#include "Animator.h"

using millisec = std::chrono::milliseconds;

Animator::Animator(std::unique_ptr<IHost> pHost)
	: m_pHost(std::move(pHost))
{
}

bool Animator::Play(IAnimation* pAnimation, bool bShouldLoop)
{
	if (!pAnimation)
	{
		return false;
	}

	if (!pAnimation->IsHostSupported(m_pHost.get()))
	{
		std::wcout << pAnimation->GetName() << L" animation is not supported on this system.\n";
		return false;
	}

	std::wcout << L"Playing " << pAnimation->GetName() << L" animation...\n\n";

	do
	{
		this->Animate(pAnimation);

	} while (bShouldLoop);

	return true;
}

bool Animator::SetSpeedFactor(float factor)
{
	if ((factor >= 0.01f) && (factor <= 2.5f))
	{
		m_speedFactor = factor;
		return true;
	}

	return false;
}

bool Animator::Animate(IAnimation* pAnimation)
{
	if (!pAnimation)
	{
		return false;
	}

	for (size_t i = 0; i < pAnimation->Size(); ++i)
	{
		if (const auto frame = pAnimation->GetFrame(i))
		{
			m_pHost->SetColour(frame->devices, frame->zone, frame->colour);
			auto const frameSleep = static_cast<uint32_t>(frame->ms_time / m_speedFactor);
			std::this_thread::sleep_for(millisec(frameSleep));
		}
	}

	return true;
}