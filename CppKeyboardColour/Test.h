#pragma once

#include "stdafx.h"
#include "WbemService.h"

void Test()
{
	auto ptrResult = WMI::Get()->ExecuteMethod(L"CLEVO_GET.InstanceName='ACPI\\PNP0C14\\0_0'", L"GetOem1", nullptr);

	CIMTYPE cimType{};
	VARIANT varValue{};
	const auto hr = ptrResult->Get(L"Data", NULL, &varValue, &cimType, nullptr);

	std::cout << "System Board ID: 0x" << (void*)varValue.uintVal << "\n";
	std::cout << "Press Enter to exit.\n";

	std::getchar();
}
