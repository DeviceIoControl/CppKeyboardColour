// Created by DeviceIoControl

#pragma once
#include "KeyboardType.h"
#include "Console.h"

Console& AppConsole();

void WaitForEnterIfNeeded();
void EnterHiddenMode(bool shouldHide);

std::ostream& operator<<(std::ostream& _Ostr, DeviceMask devices);
std::ostream& operator<<(std::ostream& _Ostr, KeyboardType kbType);