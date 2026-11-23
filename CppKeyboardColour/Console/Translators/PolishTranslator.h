// Created by DeviceIoControl

#pragma once
#include "ITranslator.h"
#include "../LogLevel.h"

#define POLISH_PROGRAM_NAME L"Narzędzie do zmiany kolorów klawiatury CLEVO"

class PolishTranslator
	: public ITranslator
{
public:
	PolishTranslator() = default;
	~PolishTranslator() override = default;

	std::wstring Translate(const std::wstring& msg) override;
	std::wstring Translate(LogLevel level) override;
	bool IsCompatible(LANGID langId) const override;

private:
	std::unordered_map<std::wstring, std::wstring> m_mapping
	{
		{ RELEASE_BUILD_STRING, MAKE_RELEASE_BUILD_STRING(POLISH_PROGRAM_NAME, L"Utworzone przez DeviceIoControl.")},
		{ TEST_BUILD_STRING, MAKE_NONRELEASE_BUILD_STRING(POLISH_PROGRAM_NAME, L"Wersja testowa", L"Utworzone przez DeviceIoControl.") },
		{ DEBUG_BUILD_STRING, MAKE_NONRELEASE_BUILD_STRING(POLISH_PROGRAM_NAME, L"Wersja debugowa", L"Utworzone przez DeviceIoControl.") },
		{ L"Detected Model ID: 0x%08X", L"Wykryty identyfikator modelu: 0x%08X" },
		{ L"Host Devices: %s", L"Urządzenia hosta: %s" },
		{ L"Keyboard Type: %s", L"Typ klawiatury: %s" },
		{ L"Model Name: %s", L"Nazwa modelu: %s" },
		{ L"Custom speed: %0.f%%\n", L"Niestandardowa prędkość: %0.f%%\n" },
		{ L"Device monitor mode enabled! (Performance may be affected)", L"Tryb monitorowania urządzenia włączony! (Wydajność może ulec pogorszeniu)"},
		{ L"{%s} - Code: 0x%08X -> %s Colour: (RED: 0x%08X), (GREEN: 0x%08X), (BLUE: 0x%08X)", L"{%s} - Kod: 0x%08X -> %s Kolor: (CZERWONY: 0x%08X), (ZIELONY: 0x%08X), (NIEBIESKI: 0x%08X)"},
		{ L"Speed value out of range (1-250) - Will use default speed.", L"Wartość prędkości spoza zakresu (1–250) – zostanie użyta prędkość domyślna."},
		{ L"Playing '%s' animation...", L"Odtwarzanie animacji „%s”..."},
		{ L"'%s' animation is not supported on this system.", L"Animacja „%s” nie jest obsługiwana w tym systemie."},
		{ L"Cannot load %s. Please ensure the DLL is within the same directory!", L"Nie można załadować %s. Upewnij się, że plik DLL znajduje się w tym samym katalogu!" },
		{ L"Cannot load clevomof.dll.\nPlease ensure the DLL is registered correctly.", L"Nie można załadować pliku clevomof.dll.\nUpewnij się, że plik DLL jest poprawnie zarejestrowany."},
		{ L"Cannot load clevomof.dll.", L"Nie można załadować pliku clevomof.dll." },
		{ L"Cannot load clevomof.dll.\nPlease ensure the DLL is at: %s", L"Nie można załadować pliku clevomof.dll.\nUpewnij się, że plik DLL znajduje się w lokalizacji: %s"},
		{ L"CLEVOMOF.dll is registered - Failed to access code.\nPlease restart your system and try again.", L"Plik CLEVOMOF.dll został zarejestrowany – nie udało się uzyskać dostępu do kodu.\nUruchom ponownie system i spróbuj ponownie."},
		{ L"Turning backlights on.", L"Włączanie podświetlenia."},
		{ L"Turning backlights off.", L"Wyłączanie podświetlenia."},
		{ L"This operation is not supported on this system.", L"Ta operacja nie jest obsługiwana w tym systemie." },
		{ L"Playing Inbuilt Keyboard animation...", L"Odtwarzanie animacji wbudowanej klawiatury..." },
		{ L"Setting user provided colour...", L"Ustawianie koloru wskazanego przez użytkownika..." },
		{ L"This operation is not supported on this keyboard type.", L"Ta operacja nie jest obsługiwana w przypadku tego typu klawiatury."},
		{ L"Invalid argument: Must specify 3 hexadecimal colour values.", L"Nieprawidłowy argument: Należy podać 3 wartości kolorów w formacie szesnastkowym." },
		{ L"Setting user provided zone colours...", L"Ustawianie kolorów stref określonych przez użytkownika..." },
		{ L"Setting user provided lightbar colour...", L"Ustawianie koloru paska świetlnego wskazanego przez użytkownika..." },
		{ L"An invalid command was provided.", L"Podano nieprawidłowe polecenie." },
		{ L"Exiting...", L"Wychodzenie..." },
		{ L"Invalid inbuilt animation name was provided.", L"Podano nieprawidłową nazwę wbudowanej animacji." },
		{ L"Invalid theme command.", L"Nieprawidłowe polecenie motywu." },
		{ L"Invalid animation name was provided!", L"Podano nieprawidłową nazwę animacji!" },
		{ L"Failed to parse speed input! Fallback to default speed.", L"Nie udało się przetworzyć podanej prędkości! Przyjęto prędkość domyślną." },
		{ L"You can only have 1 instance of this program running. Please close any other instances.", L"Może być uruchomiona tylko jedna instancja tego programu. Zamknij pozostałe instancje." },
		{ L"This system is not supported.\nPlease request for support using the following URL: https://github.com/DeviceIoControl/CppKeyboardColour/issues/new/choose.", L"Ten system nie jest obsługiwany.\nProsimy o zgłoszenie problemu, korzystając z następującego adresu URL: https://github.com/DeviceIoControl/CppKeyboardColour/issues/new/choose." },
		{ L"Cannot enable hidden mode with Device monitor mode enabled.", L"Nie można włączyć trybu ukrytego, gdy aktywny jest tryb monitorowania urządzenia." },
		{ L"Invalid command line. Command is: CLEVO_KeyboardColour.exe theme/inbuilt/backlight/lightbar/colour(s) [<themeName>/<hexColour>] [--once] [--speed] <speed> [--dmm] [--hide]", L"Nieprawidłowy wiersz poleceń. Polecenie ma postać: CLEVO_KeyboardColour.exe theme/inbuilt/backlight/lightbar/colour(s) [<nazwaMotywu>/<kolorWFormacieHex>] [--once] [--speed] <szybkość> [--dmm] [--hide]" },
		{ L"Cannot communicate with the requested device.", L"Nie można nawiązać komunikacji z żądanym urządzeniem." },
		{ L"Failed to detect the host's RGB devices.", L"Nie udało się wykryć urządzeń RGB hosta." },
		{ L"Failed to detected Model ID.", L"Nie udało się wykryć identyfikatora modelu." },
		{ L"\nPress ENTER to exit.", L"\nNaciśnij ENTER, aby wyjść." },
		{ L"Device monitor mode is not configured correctly! Fallback to default mode.", L"Tryb monitorowania urządzenia nie został poprawnie skonfigurowany! Przywrócono tryb domyślny." },
		{ L"{%s} - %s failed with error status: 0x%08x.", L"{%s} - %s nie powiodło się, wystąpił błąd: 0x%08x." }
	};
};