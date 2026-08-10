// Created by DeviceIoControl

#pragma once
#include "IHost.h"

DWORD DoHostDeviceOperation(std::unique_ptr<IHost> pHost, const std::vector<std::wstring>& cmdLines);