// Created by DeviceIoControl

#pragma once
#include "ITranslator.h"
#include "../LogLevel.h"

#define CHINESE_TRADITIONAL_PROGRAM_NAME L"CLEVO 鍵盤顏色工具"

class ChineseTraditionalTranslator
	: public ITranslator
{
public:
	ChineseTraditionalTranslator() = default;
	~ChineseTraditionalTranslator() override = default;

	std::wstring Translate(const std::wstring& msg) override;
	std::wstring Translate(LogLevel level) override;
	bool IsCompatible(LANGID langId) const override;

private:
	std::unordered_map<std::wstring, std::wstring> m_mapping
	{
		{ RELEASE_BUILD_STRING, MAKE_RELEASE_BUILD_STRING(CHINESE_TRADITIONAL_PROGRAM_NAME, L"由 DeviceIoControl 建立。") },
		{ TEST_BUILD_STRING, MAKE_NONRELEASE_BUILD_STRING(CHINESE_TRADITIONAL_PROGRAM_NAME, L"測試版本" , L"由 DeviceIoControl 建立。") },
		{ DEBUG_BUILD_STRING, MAKE_NONRELEASE_BUILD_STRING(CHINESE_TRADITIONAL_PROGRAM_NAME, L"偵錯版本", L"由 DeviceIoControl 建立。") },
		{ L"Detected Model ID: 0x%08X", L"偵測到的模型標識符: 0x%08X" },
		{ L"Host Devices: %s", L"主機裝置: %s"},
		{ L"Keyboard Type: %s", L"鍵盤類型: %s" },
		{ L"Model Name: %s", L"型號名稱: %s"},
		{ L"Custom speed: %0.f%%\n", L"自訂速度: %0.f%%\n" },
		{ L"Device monitor mode enabled! (Performance may be affected)", L"設備監控模式已啟用！ （性能可能會受到影響）"},
		{ L"{%s} - Code: 0x%08X -> %s Colour: (RED: 0x%08X), (GREEN: 0x%08X), (BLUE: 0x%08X)", L"{%s} — 程式碼: 0x%08X -> %s 顏色: (紅色的: 0x%08X), (綠色的: 0x%08X), (藍色的: 0x%08X)"},
		{ L"Speed value out of range (1-250) - Will use default speed.", L"速度值超出範圍（一-二百五十）－將使用預設速度。"},
		{ L"Playing '%s' animation...", L"正在播放“%s”動畫…"},
		{ L"'%s' animation is not supported on this system.", L"此系統不支援“%s”動畫。"},
		{ L"Cannot load %s. Please ensure the DLL is within the same directory!", L"無法加載 %s。請確保該 DLL 位於同一目錄下!" },
		{ L"Cannot load clevomof.dll.\nPlease ensure the DLL is registered correctly.", L"無法載入 clevomof.dll。\n請確保該 DLL 已正確註冊。"},
		{ L"Cannot load clevomof.dll.", L"無法載入 clevomof.dll。" },
		{ L"Cannot load clevomof.dll.\nPlease ensure the DLL is at: %s", L"無法載入 clevomof.dll。\n請確保該 DLL 檔案位於以下位置: %s"},
		{ L"CLEVOMOF.dll is registered - Failed to access code.\nPlease restart your system and try again.", L"CLEVOMOF.dll 已註冊－無法存取代碼。\n請重啟系統後再試。"},
		{ L"Turning backlights on.", L"開啟背光。"},
		{ L"Turning backlights off.", L"關閉背光。"},
		{ L"This operation is not supported on this system.", L"此系統不支援該操作。" },
		{ L"Playing Inbuilt Keyboard animation...", L"正在播放內建鍵盤動畫…" },
		{ L"Setting user provided colour...", L"正在設定使用者指定的顏色…" },
		{ L"This operation is not supported on this keyboard type.", L"此操作在此鍵盤類型上不受支援。"},
		{ L"Invalid argument: Must specify 3 hexadecimal colour values.", L"參數無效：必須指定 三 個十六進位顏色值。" },
		{ L"Setting user provided zone colours...", L"正在設定使用者指定的區域顏色…" },
		{ L"Setting user provided lightbar colour...", L"正在設定使用者指定的光條顏色…" },
		{ L"An invalid command was provided.", L"提供了無效命令。" },
		{ L"Exiting...", L"正在退出…" },
		{ L"Invalid inbuilt animation name was provided.", L"提供了無效的內建動畫名稱。" },
		{ L"Invalid theme command.", L"無效的主題命令。" },
		{ L"Invalid animation name was provided!", L"提供了無效的動畫名稱!" },
		{ L"Failed to parse speed input! Fallback to default speed.", L"無法解析速度輸入! 已回退至預設速度。" },
		{ L"You can only have 1 instance of this program running. Please close any other instances.", L"此程式僅允許運行一個實例。請關閉其他正在執行的實例。" },
		{ L"This system is not supported.\nPlease request for support using the following URL: https://github.com/DeviceIoControl/CppKeyboardColour/issues/new/choose.", L"此系統不受支援。\n請透過以下網址尋求支援: https://github.com/DeviceIoControl/CppKeyboardColour/issues/new/choose。" },
		{ L"Cannot enable hidden mode with Device monitor mode enabled.", L"在已啟用「裝置監控模式」的情況下，無法開啟「隱藏模式」。" },
		{ L"Invalid command line. Command is: CLEVO_KeyboardColour.exe theme/inbuilt/backlight/lightbar/colour(s) [<themeName>/<hexColour>] [--once] [--speed] <speed> [--dmm] [--hide]", L"命令列無效。指令格式為：CLEVO_KeyboardColour.exe theme/inbuilt/backlight/lightbar/colour(s) [<主題名稱>/<十六進位顏色值>] [--once] [--speed] <速度值> [--dmm] [--hide]" },
		{ L"Cannot communicate with the requested device.", L"無法與所要求的設備進行通訊。" },
		{ L"Failed to detect the host's RGB devices.", L"未能偵測到主機的 RGB 裝置。" },
		{ L"Failed to detected Model ID.", L"未能偵測到型號識別碼。" },
		{ L"\nPress ENTER to exit.", L"\n按回車鍵退出。" },
		{ L"Device monitor mode is not configured correctly! Fallback to default mode.", L"裝置監控模式設定不正確! 已回復為預設模式。" },
		{ L"{%s} - %s failed with error status: 0x%08x.", L"{%s} - %s 因錯誤狀態而失敗: 0x%08x." }
	};
};