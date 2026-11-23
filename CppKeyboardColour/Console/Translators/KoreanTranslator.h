// Created by DeviceIoControl

#pragma once
#include "ITranslator.h"
#include "../LogLevel.h"

#define KOREAN_PROGRAM_NAME L"CLEVO 키보드 색상 도구"

class KoreanTranslator
	: public ITranslator
{
public:
	KoreanTranslator() = default;
	~KoreanTranslator() override = default;

	std::wstring Translate(const std::wstring& msg) override;
	std::wstring Translate(LogLevel level) override;
	bool IsCompatible(LANGID langId) const override;

private:
	std::unordered_map<std::wstring, std::wstring> m_mapping
	{
		{ RELEASE_BUILD_STRING, MAKE_RELEASE_BUILD_STRING(KOREAN_PROGRAM_NAME, L"DeviceIoControl에 의해 생성됨.") },
		{ TEST_BUILD_STRING, MAKE_NONRELEASE_BUILD_STRING(KOREAN_PROGRAM_NAME, L"테스트 빌드" , L"DeviceIoControl에 의해 생성됨.") },
		{ DEBUG_BUILD_STRING, MAKE_NONRELEASE_BUILD_STRING(KOREAN_PROGRAM_NAME, L"디버그 빌드", L"DeviceIoControl에 의해 생성됨.") },
		{ L"Detected Model ID: 0x%08X", L"감지된 모델 식별자: 0x%08X" },
		{ L"Host Devices: %s", L"호스트 장치: %s"},
		{ L"Keyboard Type: %s", L"키보드 유형: %s" },
		{ L"Model Name: %s", L"모델명: %s"},
		{ L"Custom speed: %0.f%%\n", L"사용자 지정 속도: %0.f%%\n" },
		{ L"Device monitor mode enabled! (Performance may be affected)", L"기기 모니터 모드가 활성화되었습니다! (성능에 영향을 줄 수 있습니다)"},
		{ L"{%s} - Code: 0x%08X -> %s Colour: (RED: 0x%08X), (GREEN: 0x%08X), (BLUE: 0x%08X)", L"{%s} — 암호: 0x%08X -> %s 색상: (빨간색: 0x%08X), (녹색: 0x%08X), (파란색: 0x%08X)"},
		{ L"Speed value out of range (1-250) - Will use default speed.", L"속도 값이 범위를 벗어났습니다(일~이백오십) - 기본 속도를 사용합니다."},
		{ L"Playing '%s' animation...", L"'%s' 애니메이션을 재생 중..."},
		{ L"'%s' animation is not supported on this system.", L"이 시스템에서는 '%s' 애니메이션을 지원하지 않습니다."},
		{ L"Cannot load %s. Please ensure the DLL is within the same directory!", L"%s 을(를) 불러올 수 없습니다. DLL이 같은 디렉토리에 있는지 확인해 주십시오!" },
		{ L"Cannot load clevomof.dll.\nPlease ensure the DLL is registered correctly.", L"clevomof.dll 파일을 불러올 수 없습니다.\n해당 DLL이 올바르게 등록되어 있는지 확인해 주십시오."},
		{ L"Cannot load clevomof.dll.", L"clevomof.dll 파일을 불러올 수 없습니다." },
		{ L"Cannot load clevomof.dll.\nPlease ensure the DLL is at: %s", L"clevomof.dll 파일을 불러올 수 없습니다.\n해당 DLL 파일이 다음 위치에 있는지 확인해 주십시오: %s"},
		{ L"CLEVOMOF.dll is registered - Failed to access code.\nPlease restart your system and try again.", L"CLEVOMOF.dll이 등록되었습니다. 코드에 액세스하지 못했습니다.\n시스템을 다시 시작한 후 다시 시도해 주십시오."},
		{ L"Turning backlights on.", L"백라이트를 켭니다."},
		{ L"Turning backlights off.", L"백라이트 끄기."},
		{ L"This operation is not supported on this system.", L"이 작업은 이 시스템에서 지원되지 않습니다." },
		{ L"Playing Inbuilt Keyboard animation...", L"내장 키보드 애니메이션 재생 중..." },
		{ L"Setting user provided colour...", L"사용자가 지정한 색상을 설정하는 중..." },
		{ L"This operation is not supported on this keyboard type.", L"이 키보드 유형에서는 이 작업을 지원하지 않습니다."},
		{ L"Invalid argument: Must specify 3 hexadecimal colour values.", L"잘못된 인수: 삼개의 16진수 색상 값을 지정해야 합니다." },
		{ L"Setting user provided zone colours...", L"사용자가 지정한 구역 색상을 설정하는 중..." },
		{ L"Setting user provided lightbar colour...", L"사용자가 지정한 라이트바 색상을 설정하는 중..." },
		{ L"An invalid command was provided.", L"유효하지 않은 명령이 입력되었습니다." },
		{ L"Exiting...", L"종료 중..." },
		{ L"Invalid inbuilt animation name was provided.", L"유효하지 않은 내장 애니메이션 이름이 제공되었습니다." },
		{ L"Invalid theme command.", L"유효하지 않은 테마 명령어입니다." },
		{ L"Invalid animation name was provided!", L"유효하지 않은 애니메이션 이름이 제공되었습니다!" },
		{ L"Failed to parse speed input! Fallback to default speed.", L"속도 입력값을 해석하지 못했습니다! 기본 속도로 전환합니다." },
		{ L"You can only have 1 instance of this program running. Please close any other instances.", L"이 프로그램은 하나만 실행할 수 있습니다. 다른 실행 중인 인스턴스를 닫아 주십시오." },
		{ L"This system is not supported.\nPlease request for support using the following URL: https://github.com/DeviceIoControl/CppKeyboardColour/issues/new/choose.", L"이 시스템은 지원되지 않습니다.\n다음 URL을 통해 지원을 요청해 주십시오: https://github.com/DeviceIoControl/CppKeyboardColour/issues/new/choose." },
		{ L"Cannot enable hidden mode with Device monitor mode enabled.", L"기기 모니터링 모드가 활성화된 상태에서는 숨김 모드를 사용할 수 없습니다." },
		{ L"Invalid command line. Command is: CLEVO_KeyboardColour.exe theme/inbuilt/backlight/lightbar/colour(s) [<themeName>/<hexColour>] [--once] [--speed] <speed> [--dmm] [--hide]", L"잘못된 명령줄입니다. 명령어 형식: CLEVO_KeyboardColour.exe theme/inbuilt/backlight/lightbar/colour(s) [<테마 이름>/<16진수 색상>] [--once] [--speed] <speed> [--dmm] [--hide]" },
		{ L"Cannot communicate with the requested device.", L"요청한 장치와 통신할 수 없습니다." },
		{ L"Failed to detect the host's RGB devices.", L"호스트의 RGB 장치를 감지하지 못했습니다." },
		{ L"Failed to detected Model ID.", L"모델 식별자를 감지하지 못했습니다." },
		{ L"\nPress ENTER to exit.", L"\n종료하려면 ENTER 키를 누르세요." },
		{ L"Device monitor mode is not configured correctly! Fallback to default mode.", L"장치 모니터 모드가 올바르게 설정되지 않았습니다! 기본 모드로 전환합니다." },
		{ L"{%s} - %s failed with error status: 0x%08x.", L"{%s} - %s 오류 상태로 실패함: 0x%08x." }
	};
};