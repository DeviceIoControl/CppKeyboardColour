// Created by DeviceIoControl

#pragma once

#include "IHost.h"
#include "Animations/IAnimation.h"

class Animator
{
public:
	Animator(std::unique_ptr<IHost> pHost);

	bool Play(IAnimation* pAnimation, bool bShouldLoop);
	bool SetSpeedFactor(float factor);

	~Animator() = default;

private:
	float m_speedFactor = 1.0f;
	std::unique_ptr<IHost> m_pHost;

	void Animate(IAnimation* pAnimation);
};