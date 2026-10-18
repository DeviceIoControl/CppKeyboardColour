// Created by DeviceIoControl

#pragma once
#include "LogLevel.h"

class ILogger
{
public:
	virtual bool Write(LogLevel level, const std::wstring& msg) = 0;
	virtual ~ILogger() = default;
};