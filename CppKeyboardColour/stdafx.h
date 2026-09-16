#pragma once
#include "targetver.h"

#define NOMINMAX

#include <iostream>
#include <cstdint>
#include <vector>
#include <optional>
#include <array>
#include <string>
#include <memory>
#include <map>
#include <future>
#include <algorithm>
#include <cwctype>

#include <Windows.h>
#include <comdef.h>
#include <wbemidl.h>

#include "ExtendedStl.h"

#pragma comment(lib, "wbemuuid.lib")

#define IS_HANDLE_VALID(handle) (handle && handle != INVALID_HANDLE_VALUE)

#ifdef _DEBUG
#define USE_DEBUGGABLE_HOST true
#define PROGRAM_BOOTSTRAP_STRING "CLEVO Keyboard Colours Tool 1.26.XXXX (Debug) - Created by DeviceIoControl."
#else
#define USE_DEBUGGABLE_HOST false
#define PROGRAM_BOOTSTRAP_STRING "CLEVO Keyboard Colours Tool 1.26.1005 - Created by DeviceIoControl."
#endif