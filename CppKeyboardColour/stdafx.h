// Written by DeviceIoControl

#pragma once
#include "targetver.h"

#define NOMINMAX
#define _CRT_SECURE_NO_WARNINGS

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

#define CP_UTF16 65001

#define DEBUG_BUILD_STRING L"CLEVO Keyboard Colours Tool 1.26.XXXX (Debug Build) - Created by DeviceIoControl."
#define TEST_BUILD_STRING L"CLEVO Keyboard Colours Tool 1.26.XXXX (Test Build) - Created by DeviceIoControl."
#define RELEASE_BUILD_STRING L"CLEVO Keyboard Colours Tool 1.26.1102 - Created by DeviceIoControl."

#if defined(DEBUG_BUILD)
#define USE_DEBUGGABLE_HOST true
#define PROGRAM_BOOTSTRAP_STRING DEBUG_BUILD_STRING
#elif defined (TEST_BUILD)
#define USE_DEBUGGABLE_HOST false
#define PROGRAM_BOOTSTRAP_STRING TEST_BUILD_STRING
#elif defined (RELEASE_BUILD)
#define USE_DEBUGGABLE_HOST false
#define PROGRAM_BOOTSTRAP_STRING RELEASE_BUILD_STRING
#endif

