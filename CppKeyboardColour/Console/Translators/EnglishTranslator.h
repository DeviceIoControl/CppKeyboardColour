// Created by DeviceIoControl

#pragma once
#include "ITranslator.h"
#include "../LogLevel.h"

class EnglishTranslator 
	: public ITranslator
{
public:
	EnglishTranslator() = default;
	~EnglishTranslator() override = default;

	std::wstring Translate(const std::wstring& msg) override;
	std::wstring Translate(LogLevel level) override;
};