// Created by DeviceIoControl

#pragma once
#include "ITranslator.h"
#include "../LogLevel.h"

#define CHINESE_SIMPLIFIED_PROGRAM_NAME L"CLEVO 键盘色彩工具"

class ChineseSimplifiedTranslator
	: public ITranslator
{
public:
	ChineseSimplifiedTranslator() = default;
	~ChineseSimplifiedTranslator() override = default;

	std::wstring Translate(const std::wstring& msg) override;
	std::wstring Translate(LogLevel level) override;
	bool IsCompatible(LANGID langId) const override;

private:
	std::unordered_map<std::wstring, std::wstring> m_mapping
	{
		{ RELEASE_BUILD_STRING, MAKE_RELEASE_BUILD_STRING(CHINESE_SIMPLIFIED_PROGRAM_NAME, L"由 DeviceIoControl 创建") },
		{ TEST_BUILD_STRING, MAKE_NONRELEASE_BUILD_STRING(CHINESE_SIMPLIFIED_PROGRAM_NAME, L"测试版本" , L"由 DeviceIoControl 创建") },
		{ DEBUG_BUILD_STRING, MAKE_NONRELEASE_BUILD_STRING(CHINESE_SIMPLIFIED_PROGRAM_NAME, L"调试版本", L"由 DeviceIoControl 创建") },
		{ L"Detected Model ID: 0x%08X", L"检测到的模型标识符: 0x%08X" },
		{ L"Host Devices: %s", L"主机设备: %s" },
		{ L"Keyboard Type: %s", L"键盘类型: %s" },
		{ L"Model Name: %s", L"型号名称: %s" },
		{ L"Custom speed: %0.f%%\n", L"自定义速度: %0.f%%\n" },
		{ L"Device monitor mode enabled! (Performance may be affected)", L"设备监控模式已启用!（性能可能会受到影响）" },
		{ L"{%s} - Code: 0x%08X -> %s Colour: (RED: 0x%08X), (GREEN: 0x%08X), (BLUE: 0x%08X)", L"{%s} — 代码: 0x%08X -> %s 颜色: (红色的: 0x%08X), (绿色的: 0x%08X), (蓝色的: 0x%08X)" },
		{ L"Speed value out of range (1-250) - Will use default speed.", L"速度值超出范围（一-二百五十）——将使用默认速度。"},
		{ L"Playing '%s' animation...", L"正在播放 '%s' 动画……" },
		{ L"'%s' animation is not supported on this system.", L"此系统不支持 '%s' 动画。" },
		{ L"Cannot load %s. Please ensure the DLL is within the same directory!", L"无法加载 %s。请确保该 DLL 位于同一目录下!" },
		{ L"Cannot load clevomof.dll.\nPlease ensure the DLL is registered correctly.", L"无法加载 clevomof.dll。\n请确保该 DLL 已正确注册。"},
		{ L"Cannot load clevomof.dll.", L"无法加载 clevomof.dll。" },
		{ L"Cannot load clevomof.dll.\nPlease ensure the DLL is at: %s", L"无法加载 clevomof.dll。\n请确保该 DLL 文件位于以下位置：%s" },
		{ L"CLEVOMOF.dll is registered - Failed to access code.\nPlease restart your system and try again.", L"CLEVOMOF.dll 已注册——无法访问代码。\n请重启系统后再试。"},
		{ L"Turning backlights on.", L"开启背光。" },
		{ L"Turning backlights off.", L"关闭背光。" },
		{ L"This operation is not supported on this system.", L"此系统不支持该操作。" },
		{ L"Playing Inbuilt Keyboard animation...", L"正在播放内置键盘动画……" },
		{ L"Setting user provided colour...", L"正在设置用户指定的颜色……" },
		{ L"This operation is not supported on this keyboard type.", L"此操作在此键盘类型上不受支持。" },
		{ L"Invalid argument: Must specify 3 hexadecimal colour values.", L"参数无效：必须指定 三 个十六进制颜色值。" },
		{ L"Setting user provided zone colours...", L"正在设置用户指定的区域颜色……" },
		{ L"Setting user provided lightbar colour...", L"正在设置用户指定的光条颜色……" },
		{ L"An invalid command was provided.", L"提供了无效命令。" },
		{ L"Exiting...", L"正在退出……" },
		{ L"Invalid inbuilt animation name was provided.", L"提供了无效的内置动画名称。" },
		{ L"Invalid theme command.", L"无效的主题命令。" },
		{ L"Invalid animation name was provided!", L"提供了无效的动画名称!" },
		{ L"Failed to parse speed input! Fallback to default speed.", L"无法解析速度输入! 已回退至默认速度。" },
		{ L"You can only have 1 instance of this program running. Please close any other instances.", L"此程序仅允许运行一个实例。请关闭其他正在运行的实例。" },
		{ L"This system is not supported.\nPlease request for support using the following URL: https://github.com/DeviceIoControl/CppKeyboardColour/issues/new/choose.", L"此系统不受支持。\n请通过以下网址寻求支持：https://github.com/DeviceIoControl/CppKeyboardColour/issues/new/choose。" },
		{ L"Cannot enable hidden mode with Device monitor mode enabled.", L"在已启用“设备监控模式”的情况下，无法开启“隐藏模式”。" },
		{ L"Invalid command line. Command is: CLEVO_KeyboardColour.exe theme/inbuilt/backlight/lightbar/colour(s) [<themeName>/<hexColour>] [--once] [--speed] <speed> [--dmm] [--hide]", L"命令行无效。命令格式为：CLEVO_KeyboardColour.exe theme/inbuilt/backlight/lightbar/colour(s) [<主题名称>/<十六进制颜色值>] [--once] [--speed] <速度值> [--dmm] [--hide]" },
		{ L"Cannot communicate with the requested device.", L"无法与所请求的设备进行通信。" },
		{ L"Failed to detect the host's RGB devices.", L"未能检测到主机的 RGB 设备。" },
		{ L"Failed to detected Model ID.", L"未能检测到型号标识符。" },
		{ L"\nPress ENTER to exit.", L"\n按回车键退出。" },
		{ L"Device monitor mode is not configured correctly! Fallback to default mode.", L"设备监控模式配置不正确! 已回退至默认模式。" },
		{ L"{%s} - %s failed with error status: 0x%08x.", L"{%s} - %s 失败，错误状态: 0x%08x." }
	};
};