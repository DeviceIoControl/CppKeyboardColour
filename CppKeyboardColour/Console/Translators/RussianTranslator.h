// Created by DeviceIoControl

#pragma once
#include "ITranslator.h"
#include "../LogLevel.h"

#define RUSSIAN_PROGRAM_NAME L"Утилита для настройки цвета клавиатуры CLEVO"

class RussianTranslator
	: public ITranslator
{
public:
	RussianTranslator() = default;
	~RussianTranslator() override = default;

	std::wstring Translate(const std::wstring& msg) override;
	std::wstring Translate(LogLevel level) override;
	bool IsCompatible(LANGID langId) const override;

private:
	std::map<std::wstring, std::wstring> m_mapping
	{
		{ RELEASE_BUILD_STRING, MAKE_RELEASE_BUILD_STRING(RUSSIAN_PROGRAM_NAME, L"Создано с помощью DeviceIoControl.") },
		{ TEST_BUILD_STRING, MAKE_NONRELEASE_BUILD_STRING(RUSSIAN_PROGRAM_NAME, L"тестовая сборка" , L"Создано с помощью DeviceIoControl.") },
		{ DEBUG_BUILD_STRING, MAKE_NONRELEASE_BUILD_STRING(RUSSIAN_PROGRAM_NAME, L"отладочная сборка" , L"Создано с помощью DeviceIoControl.") },
		{ L"Detected Model ID: 0x%08X", L"Идентификатор обнаруженной модели: 0x%08X"},
		{ L"Host Devices: %s", L"Хост-устройства: %s"},
		{ L"Keyboard Type: %s", L"Тип клавиатуры: %s" },
		{ L"Model Name: %s", L"Название модели: %s"},
		{ L"Device monitor mode enabled! (Performance may be affected)", L"Включен режим мониторинга устройства! (Производительность может снизиться)"},
		{ L"{%s} - Code: 0x%08X -> %s Colour: (RED: 0x%08X), (GREEN: 0x%08X), (BLUE: 0x%08X)", L"{%s} - Код: 0x%08X -> %s Цвет: (КРАСНЫЙ: 0x%08X), (ЗЕЛЕНЫЙ: 0x%08X), (СИНИЙ: 0x%08X)"},
		{ L"Speed value out of range (1-250) - Will use default speed.", L"Значение скорости вне допустимого диапазона (1–250) - будет использована скорость по умолчанию."},
		{ L"Playing '%s' animation...", L"Воспроизведение анимации '%s'..."},
		{ L"'%s' animation is not supported on this system.", L"Анимация '%s' не поддерживается в этой системе."},
		{ L"Cannot load %s. Please ensure the DLL is within the same directory!", L"Не удается загрузить %s. Убедитесь, что DLL-файл находится в той же директории!" },
		{ L"Cannot load clevomof.dll.\nPlease ensure the DLL is registered correctly.", L"Не удается загрузить clevomof.dll.\nПожалуйста, убедитесь, что этот DLL-файл правильно зарегистрирован."},
		{ L"Cannot load clevomof.dll.", L"Не удается загрузить clevomof.dll." },
		{ L"Cannot load clevomof.dll.\nPlease ensure the DLL is at: %s", L"Не удается загрузить clevomof.dll.\nУбедитесь, что этот DLL-файл находится по адресу: %s"},
		{ L"CLEVOMOF.dll is registered - Failed to access code.\nPlease restart your system and try again.", L"Файл CLEVOMOF.dll зарегистрирован, но получить доступ к коду не удалось.\nПожалуйста, перезагрузите систему и повторите попытку."},
		{ L"Turning backlights on.", L"Включение подсветки."},
		{ L"Turning backlights off", L"Отключение подсветки."},
		{ L"This operation is not supported on this system.", L"Эта операция не поддерживается в данной системе." },
		{ L"Playing Inbuilt Keyboard animation...", L"Воспроизведение анимации встроенной клавиатуры..." },
		{ L"Setting user provided colour...", L"Установка цвета, заданного пользователем..." },
		{ L"This operation is not supported on this keyboard type.", L"Эта операция не поддерживается для данного типа клавиатуры."},
		{ L"Invalid argument: Must specify 3 hexadecimal colour values.", L"Недопустимый аргумент: необходимо указать 3 шестнадцатеричных значения цвета." },
		{ L"Setting user provided zone colours...", L"Установка заданных пользователем цветов зон..." },
		{ L"Setting user provided lightbar colour...", L"Установка цвета световой панели, заданного пользователем..." },
		{ L"An invalid command was provided.", L"Была введена недопустимая команда." },
		{ L"Exiting...", L"Выход..." },
		{ L"Invalid inbuilt animation name was provided.", L"Было указано недопустимое имя встроенной анимации." },
		{ L"Invalid theme command.", L"Недопустимая команда темы." },
		{ L"Invalid animation name was provided!", L"Указано недопустимое имя анимации!" },
		{ L"Failed to parse speed input! Fallback to default speed.", L"Не удалось распознать введённое значение скорости! Используется скорость по умолчанию." },
		{ L"You can only have 1 instance of this program running. Please close any other instances.", L"Может быть запущен только один экземпляр этой программы. Пожалуйста, закройте все остальные экземпляры." },
		{ L"This system is not supported.\nPlease request for support using the following URL: https://github.com/DeviceIoControl/CppKeyboardColour/issues/new/choose.", L"Данная система не поддерживается. Пожалуйста, обратитесь за поддержкой, воспользовавшись следующей ссылкой: https://github.com/DeviceIoControl/CppKeyboardColour/issues/new/choose." },
		{ L"Cannot enable hidden mode with Device monitor mode enabled.", L"Невозможно включить скрытый режим, если активирован режим мониторинга устройства." },
		{ L"Invalid command line. Command is: CLEVO_KeyboardColour.exe theme/inbuilt/backlight/lightbar/colour(s) [<themeName>/<hexColour>] [--once] [--speed] <speed> [--dmm] [--hide]", L"Некорректная командная строка. Команда: CLEVO_KeyboardColour.exe theme/inbuilt/backlight/lightbar/colour(s) [<имя_темы>/<hex-код_цвета>] [--once] [--speed] <скорость> [--dmm] [--hide]" },
		{ L"Cannot communicate with the requested device.", L"Не удается установить связь с запрошенным устройством." },
		{ L"Failed to detect the host's RGB devices.", L"Не удалось обнаружить RGB-устройства хоста." },
		{ L"Failed to detected Model ID.", L"Не удалось определить идентификатор модели." }
	};
};