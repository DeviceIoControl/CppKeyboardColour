#pragma once

#include "stdafx.h"
#include "WbemService.h"

#define GET_PRODUCT_DLL_PATH L"C:\\Program Files (x86)\\HotKey\\GetProductdll.dll"
#define IS_HANDLE_VALID(handle) (handle && handle != INVALID_HANDLE_VALUE)

using T_GetProductID_PCI = uint32_t(__stdcall*)();

void Test()
{
	auto const hGetProductDLL = LoadLibraryW(GET_PRODUCT_DLL_PATH);

	if (!IS_HANDLE_VALID(hGetProductDLL)) 
	{
		FreeLibrary(hGetProductDLL);

		std::wcout << L"Failed to load: " << GET_PRODUCT_DLL_PATH << L"\n";
		std::cout << "Please run as Administrator. Press enter to exit.\n";

		std::getchar();

		std::exit(0);
	}

	T_GetProductID_PCI pfnGetProductID_PCI = (decltype(pfnGetProductID_PCI))GetProcAddress(hGetProductDLL, "GetProductID_PCI");

	std::cout << "Product PCI Device ID: 0x" << (void*)pfnGetProductID_PCI() << "\n";
	std::cout << "Press Enter to exit.\n";

	std::getchar();

	std::exit(0);
}
