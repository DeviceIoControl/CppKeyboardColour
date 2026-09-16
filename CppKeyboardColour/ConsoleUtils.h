// Created by DeviceIoControl

#pragma once
#include "KeyboardType.h"

void WaitForEnterIfNeeded();

std::ostream& operator<<(std::ostream& _Ostr, DeviceMask devices);
std::ostream& operator<<(std::ostream& _Ostr, KeyboardType kbType);