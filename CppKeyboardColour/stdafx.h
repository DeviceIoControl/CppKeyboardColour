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
#include <set>
#include <map>
#include <future>
#include <algorithm>

#include <Windows.h>
#include <comdef.h>
#include <wbemidl.h>

#include "ExtendedStl.h"

#pragma comment(lib, "wbemuuid.lib")

#define IS_HANDLE_VALID(handle) (handle && handle != INVALID_HANDLE_VALUE)

#ifdef _DEBUG
#define USE_DEBUGGABLE_HOST true
#else
#define USE_DEBUGGABLE_HOST false
#endif