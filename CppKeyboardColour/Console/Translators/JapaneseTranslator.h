// Created by DeviceIoControl

#pragma once
#include "ITranslator.h"
#include "../LogLevel.h"

#define JAPANESE_PROGRAM_NAME L"CLEVOキーボードカラー設定ツール"

class JapaneseTranslator
	: public ITranslator
{
public:
	JapaneseTranslator() = default;
	~JapaneseTranslator() override = default;

	std::wstring Translate(const std::wstring& msg) override;
	std::wstring Translate(LogLevel level) override;
	bool IsCompatible(LANGID langId) const override;

private:
	std::map<std::wstring, std::wstring> m_mapping
	{
		{ RELEASE_BUILD_STRING, MAKE_RELEASE_BUILD_STRING(JAPANESE_PROGRAM_NAME , L"DeviceIoControlによって作成された") },
		{ TEST_BUILD_STRING, MAKE_NONRELEASE_BUILD_STRING(JAPANESE_PROGRAM_NAME , L"テストビルド" , L"DeviceIoControlによって作成された") },
		{ DEBUG_BUILD_STRING, MAKE_NONRELEASE_BUILD_STRING(JAPANESE_PROGRAM_NAME , L"デバッグビルド", L"DeviceIoControlによって作成された") },
		{ L"Detected Model ID: 0x%08X", L"検出されたモデル識別子: 0x%08X" },
		{ L"Host Devices: %s", L"ホストデバイス: %s"},
		{ L"Keyboard Type: %s", L"キーボードの種類: %s" },
		{ L"Model Name: %s", L"モデル名: %s"},
		{ L"Custom speed: %0.f%%\n", L"カスタム速度: %0.f%%\n" },
		{ L"Device monitor mode enabled! (Performance may be affected)", L"デバイスモニターモードが有効になりました!（パフォーマンスに影響が出る可能性があります）"},
		{ L"{%s} - Code: 0x%08X -> %s Colour: (RED: 0x%08X), (GREEN: 0x%08X), (BLUE: 0x%08X)", L"{%s} — コード: 0x%08X -> %s 色: (赤: 0x%08X), (緑: 0x%08X), (青: 0x%08X)"},
		{ L"Speed value out of range (1-250) - Will use default speed.", L"速度の値が範囲外（一～二百五十）です。デフォルトの速度を使用します。"},
		{ L"Playing '%s' animation...", L"「%s」アニメーションを再生中..."},
		{ L"'%s' animation is not supported on this system.", L"このシステムでは「%s」アニメーションはサポートされていません。"},
		{ L"Cannot load %s. Please ensure the DLL is within the same directory!", L"%s を読み込めません。DLL が同じディレクトリ内にあることを確認してください!" },
		{ L"Cannot load clevomof.dll.\nPlease ensure the DLL is registered correctly.", L"clevomof.dll を読み込めません。\nDLL が正しく登録されていることを確認してください。"},
		{ L"Cannot load clevomof.dll.", L"clevomof.dll を読み込めません。" },
		{ L"Cannot load clevomof.dll.\nPlease ensure the DLL is at: %s", L"clevomof.dll を読み込めません。\nこの DLL が次の場所にあることを確認してください: %s"},
		{ L"CLEVOMOF.dll is registered - Failed to access code.\nPlease restart your system and try again.", L"CLEVOMOF.dll は登録されましたが、コードへのアクセスに失敗しました。\nシステムを再起動してから、再度お試しください。"},
		{ L"Turning backlights on.", L"バックライトをオンにします。"},
		{ L"Turning backlights off.", L"バックライトをオフにする。" },
		{ L"This operation is not supported on this system.", L"この操作は、このシステムではサポートされていません。" },
		{ L"Playing Inbuilt Keyboard animation...", L"内蔵キーボードのアニメーションを再生中..." },
		{ L"Setting user provided colour...", L"ユーザー指定の色を設定中..." },
		{ L"This operation is not supported on this keyboard type.", L"この操作は、このキーボードタイプではサポートされていません。"},
		{ L"Invalid argument: Must specify 3 hexadecimal colour values.", L"無効な引数: 16進数の色値を3つ指定する必要があります。" },
		{ L"Setting user provided zone colours...", L"ユーザー指定のゾーンカラーを設定中..." },
		{ L"Setting user provided lightbar colour...", L"ユーザーが指定したライトバーの色を設定中..." },
		{ L"An invalid command was provided.", L"無効なコマンドが指定されました。" },
		{ L"Exiting...", L"終了しています..." },
		{ L"Invalid inbuilt animation name was provided.", L"無効な組み込みアニメーション名が指定されました。" },
		{ L"Invalid theme command.", L"無効なテーマコマンドです。" },
		{ L"Invalid animation name was provided!", L"無効なアニメーション名が指定されました!" },
		{ L"Failed to parse speed input! Fallback to default speed.", L"速度入力の解析に失敗しました! デフォルトの速度を使用します。" },
		{ L"You can only have 1 instance of this program running. Please close any other instances.", L"このプログラムは1つしか起動できません。他のインスタンスを終了してください。" },
		{ L"This system is not supported.\nPlease request for support using the following URL: https://github.com/DeviceIoControl/CppKeyboardColour/issues/new/choose.", L"このシステムはサポートされていません。\nサポートを依頼するには、以下のURLを使用してください: https://github.com/DeviceIoControl/CppKeyboardColour/issues/new/choose" },
		{ L"Cannot enable hidden mode with Device monitor mode enabled.", L"デバイスモニターモードが有効な状態では、隠しモードを有効にできません。" },
		{ L"Invalid command line. Command is: CLEVO_KeyboardColour.exe theme/inbuilt/backlight/lightbar/colour(s) [<themeName>/<hexColour>] [--once] [--speed] <speed> [--dmm] [--hide]", L"コマンドラインが無効です。コマンドは以下の通りです: CLEVO_KeyboardColour.exe theme/inbuilt/backlight/lightbar/colour(s) [<テーマ名>/<16進カラーコード>] [--once] [--speed] <speed> [--dmm] [--hide]" },
		{ L"Cannot communicate with the requested device.", L"要求されたデバイスと通信できません。" },
		{ L"Failed to detect the host's RGB devices.", L"ホストのRGBデバイスを検出できませんでした。" },
		{ L"Failed to detected Model ID.", L"モデル識別子を検出できませんでした。" },
		{ L"\nPress ENTER to exit.", L"\nENTERキーを押して終了します。" }
	};
};