// Created by DeviceIoControl

#pragma once
#include "Animations.h"

std::unique_ptr<IAnimation> ProcessThemeCommandLine(const std::vector<std::wstring>& cmdLines);