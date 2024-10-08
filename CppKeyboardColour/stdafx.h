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
#include <algorithm>
#include <future>

#include <Windows.h>
#include <comdef.h>
#include <wbemidl.h>

#pragma comment(lib, "wbemuuid.lib")

#define IS_HANDLE_VALID(handle) (handle && handle != INVALID_HANDLE_VALUE)