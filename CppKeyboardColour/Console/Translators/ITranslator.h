#pragma once

#include "../LogLevel.h"

class ITranslator 
{
public:
	virtual ~ITranslator() = default;
	virtual std::wstring Translate(const std::wstring& msg) = 0;
	virtual std::wstring Translate(LogLevel level) = 0;
};