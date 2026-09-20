// Written by DeviceIoControl

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
#include <type_traits>

#include <Windows.h>
#include <comdef.h>
#include <wbemidl.h>

#include "ExtendedStl.h"

#pragma comment(lib, "wbemuuid.lib")
#pragma comment(lib, "advapi32.lib")

#define USE_LEGACY_MODEL_RETRIEVER false
#define IS_HANDLE_VALID(handle) (handle && handle != INVALID_HANDLE_VALUE)

#if defined(DEBUG_BUILD)
#define USE_DEBUGGABLE_HOST true
#define PROGRAM_BOOTSTRAP_STRING L"CLEVO Keyboard Colours Tool 1.26.XXXX (Debug Build) - Created by DeviceIoControl."
#elif defined (TEST_BUILD)
#define USE_DEBUGGABLE_HOST false
#define PROGRAM_BOOTSTRAP_STRING L"CLEVO Keyboard Colours Tool 1.26.XXXX (Test Build) - Created by DeviceIoControl."
#elif defined (RELEASE_BUILD)
#define USE_DEBUGGABLE_HOST false
#define PROGRAM_BOOTSTRAP_STRING L"CLEVO Keyboard Colours Tool 1.26.0921 - Created by DeviceIoControl."
#endif

