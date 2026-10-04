// Created by DeviceIoControl

#pragma once
#include "../Console.h"
#include "../Common/KeyboardType.h"

Console& AppConsole();

void WaitForEnterIfNeeded();
void EnterHiddenMode(bool shouldHide);
void PromptUserOnError(const std::wstring& errMessage);

std::ostream& operator<<(std::ostream& _Ostr, DeviceMask devices);
std::ostream& operator<<(std::ostream& _Ostr, KeyboardType kbType);