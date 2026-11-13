// Created by DeviceIoControl

#pragma once
#include "ITranslator.h"
#include "../LogLevel.h"

#define UKRAINIAN_PROGRAM_NAME L"Інструмент для налаштування кольорів клавіатури CLEVO"

class UkrainianTranslator
	: public ITranslator
{
public:
	UkrainianTranslator() = default;
	~UkrainianTranslator() override = default;

	std::wstring Translate(const std::wstring& msg) override;
	std::wstring Translate(LogLevel level) override;
	bool IsCompatible(LANGID langId) const override;

private:
	std::map<std::wstring, std::wstring> m_mapping
	{
		{ RELEASE_BUILD_STRING, MAKE_RELEASE_BUILD_STRING(UKRAINIAN_PROGRAM_NAME, L"створено DeviceIoControl.") },
		{ TEST_BUILD_STRING, MAKE_NONRELEASE_BUILD_STRING(UKRAINIAN_PROGRAM_NAME, L"тестова збірка" , L"створено DeviceIoControl.") },
		{ DEBUG_BUILD_STRING, MAKE_NONRELEASE_BUILD_STRING(UKRAINIAN_PROGRAM_NAME, L"налагоджувальна збірка", L"створено DeviceIoControl.") },
		{ L"Detected Model ID: 0x%08X", L"Виявлений ідентифікатор моделі: 0x%08X"},
		{ L"Host Devices: %s", L"Хост-пристрої: %s"},
		{ L"Keyboard Type: %s", L"Тип клавіатури: %s" },
		{ L"Model Name: %s", L"Назва моделі: %s"},
		{ L"Device monitor mode enabled! (Performance may be affected)", L"Увімкнено режим моніторингу пристрою! (Це може вплинути на продуктивність)"},
		{ L"{%s} - Code: 0x%08X -> %s Colour: (RED: 0x%08X), (GREEN: 0x%08X), (BLUE: 0x%08X)", L"{%s} — Код: 0x%08X -> %s Колір: (ЧЕРВОНИЙ: 0x%08X), (ЗЕЛЕНИЙ: 0x%08X), (СИНІЙ: 0x%08X)"},
		{ L"Speed value out of range (1-250) - Will use default speed.", L"Значення швидкості поза межами діапазону (1–250) — буде використано швидкість за замовчуванням."},
		{ L"Playing '%s' animation...", L"Відтворення анімації '%s'..."},
		{ L"'%s' animation is not supported on this system.", L"Анімація '%s' не підтримується в цій системі."},
		{ L"Cannot load %s. Please ensure the DLL is within the same directory!", L"Не вдається завантажити %s. Переконайтеся, що DLL-файл знаходиться в тій самій папці!" },
		{ L"Cannot load clevomof.dll.\nPlease ensure the DLL is registered correctly.", L"Не вдається завантажити clevomof.dll.\nПереконайтеся, що цей DLL-файл зареєстровано належним чином."},
		{ L"Cannot load clevomof.dll.", L"Не вдається завантажити clevomof.dll." },
		{ L"Cannot load clevomof.dll.\nPlease ensure the DLL is at: %s", L"Не вдається завантажити clevomof.dll.\nПереконайтеся, що файл DLL знаходиться за адресою: %s"},
		{ L"CLEVOMOF.dll is registered - Failed to access code.\nPlease restart your system and try again.", L"Файл CLEVOMOF.dll зареєстровано — не вдалося отримати доступ до коду.\nБудь ласка, перезапустіть систему та спробуйте ще раз."},
		{ L"Turning backlights on.", L"Увімкнення підсвічування."},
		{ L"Turning backlights off", L"Вимкнення підсвічування."},
		{ L"This operation is not supported on this system.", L"Ця операція не підтримується в цій системі." },
		{ L"Playing Inbuilt Keyboard animation...", L"Відтворення анімації вбудованої клавіатури..." },
		{ L"Setting user provided colour...", L"Встановлення кольору, заданого користувачем..." },
		{ L"This operation is not supported on this keyboard type.", L"Ця операція не підтримується для цього типу клавіатури."},
		{ L"Invalid argument: Must specify 3 hexadecimal colour values.", L"Неприпустимий аргумент: необхідно вказати 3 шістнадцяткові значення кольору." },
		{ L"Setting user provided zone colours...", L"Встановлення кольорів зон, визначених користувачем..." },
		{ L"Setting user provided lightbar colour...", L"Встановлення кольору світлової панелі, заданого користувачем..." },
		{ L"An invalid command was provided.", L"Було введено неприпустиму команду." },
		{ L"Exiting...", L"Вихід..." },
		{ L"Invalid inbuilt animation name was provided.", L"Було вказано неприпустиму назву вбудованої анімації." },
		{ L"Invalid theme command.", L"Неприпустима команда теми." },
		{ L"Invalid animation name was provided!", L"Вказано неприпустиму назву анімації!" },
		{ L"Failed to parse speed input! Fallback to default speed.", L"Не вдалося розібрати вхідне значення швидкості! Використовується швидкість за замовчуванням." },
		{ L"You can only have 1 instance of this program running. Please close any other instances.", L"Може бути запущено лише один екземпляр цієї програми. Будь ласка, закрийте всі інші екземпляри." },
		{ L"This system is not supported.\nPlease request for support using the following URL: https://github.com/DeviceIoControl/CppKeyboardColour/issues/new/choose.", L"Ця система не підтримується.\nБудь ласка, зверніться по підтримку, скориставшись цим посиланням: https://github.com/DeviceIoControl/CppKeyboardColour/issues/new/choose." },
		{ L"Cannot enable hidden mode with Device monitor mode enabled.", L"Не вдається ввімкнути прихований режим, коли активовано режим моніторингу пристрою." },
		{ L"Invalid command line. Command is: CLEVO_KeyboardColour.exe theme/inbuilt/backlight/lightbar/colour(s) [<themeName>/<hexColour>] [--once] [--speed] <speed> [--dmm] [--hide]", L"Неприпустимий командний рядок. Команда: CLEVO_KeyboardColour.exe theme/inbuilt/backlight/lightbar/colour(s) [<назва_теми>/<шістнадцятковий_код_кольору>] [--once] [--speed] <швидкість> [--dmm] [--hide]" },
		{ L"Cannot communicate with the requested device.", L"Не вдається зв’язатися із запитаним пристроєм." },
		{ L"Failed to detect the host's RGB devices.", L"Не вдалося виявити RGB-пристрої хоста." },
		{ L"Failed to detected Model ID.", L"Не вдалося визначити ідентифікатор моделі." }
	};
};