#pragma once
#include "IKeyboard.h"

DWORD DoKeyboardOperation(IKeyboard* pKeyboard, const std::vector<std::wstring>& cmdLines);