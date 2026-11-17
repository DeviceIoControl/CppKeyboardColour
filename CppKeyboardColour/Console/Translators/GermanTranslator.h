// Created by DeviceIoControl

#pragma once
#include "ITranslator.h"
#include "../LogLevel.h"

#define GERMAN_PROGRAM_NAME L"CLEVO-Tastaturfarben-Tool"

class GermanTranslator
	: public ITranslator
{
public:
	GermanTranslator() = default;
	~GermanTranslator() override = default;

	std::wstring Translate(const std::wstring& msg) override;
	std::wstring Translate(LogLevel level) override;
	bool IsCompatible(LANGID langId) const override;

private:
	std::map<std::wstring, std::wstring> m_mapping
	{
		{ RELEASE_BUILD_STRING, MAKE_RELEASE_BUILD_STRING(GERMAN_PROGRAM_NAME, L"Erstellt von DeviceIoControl.") },
		{ TEST_BUILD_STRING, MAKE_NONRELEASE_BUILD_STRING(GERMAN_PROGRAM_NAME, L"Testversion" , L"Erstellt von DeviceIoControl.") },
		{ DEBUG_BUILD_STRING, MAKE_NONRELEASE_BUILD_STRING(GERMAN_PROGRAM_NAME, L"Debug-Version" , L"Erstellt von DeviceIoControl.") },
		{ L"Detected Model ID: 0x%08X", L"Erkannte Modell-ID: 0x%08X" },
		{ L"Host Devices: %s", L"Host-Geräte: %s" },
		{ L"Keyboard Type: %s", L"Tastaturtyp: %s" },
		{ L"Model Name: %s", L"Modellname: %s" },
		{ L"Custom speed: %0.f%%\n", L"Benutzerdefinierte Geschwindigkeit: %0.f%%\n" },
		{ L"Device monitor mode enabled! (Performance may be affected)", L"Geräteüberwachungsmodus aktiviert! (Die Leistung kann beeinträchtigt werden)"},
		{ L"{%s} - Code: 0x%08X -> %s Colour: (RED: 0x%08X), (GREEN: 0x%08X), (BLUE: 0x%08X)", L"{%s} – Code: 0x%08X -> %s Farbe: (ROT: 0x%08X), (GRÜN: 0x%08X), (BLAU: 0x%08X)"},
		{ L"Speed value out of range (1-250) - Will use default speed.", L"Geschwindigkeitswert außerhalb des zulässigen Bereichs (1–250) – Standardgeschwindigkeit wird verwendet."},
		{ L"Playing '%s' animation...", L"Animation „%s“ wird abgespielt..."},
		{ L"'%s' animation is not supported on this system.", L"Die Animation „%s“ wird auf diesem System nicht unterstützt."},
		{ L"Cannot load %s. Please ensure the DLL is within the same directory!", L"%s kann nicht geladen werden. Bitte stellen Sie sicher, dass sich die DLL im selben Verzeichnis befindet!" },
		{ L"Cannot load clevomof.dll.\nPlease ensure the DLL is registered correctly.", L"Die Datei „clevomof.dll“ kann nicht geladen werden.\nBitte stellen Sie sicher, dass die DLL ordnungsgemäß registriert ist."},
		{ L"Cannot load clevomof.dll.", L"Die Datei clevomof.dll kann nicht geladen werden." },
		{ L"Cannot load clevomof.dll.\nPlease ensure the DLL is at: %s", L"Die Datei „clevomof.dll“ kann nicht geladen werden.\nBitte stellen Sie sicher, dass sich die DLL unter folgendem Pfad befindet: %s"},
		{ L"CLEVOMOF.dll is registered - Failed to access code.\nPlease restart your system and try again.", L"CLEVOMOF.dll ist registriert – Zugriff auf den Code fehlgeschlagen.\nBitte starten Sie Ihr System neu und versuchen Sie es erneut."},
		{ L"Turning backlights on.", L"Hintergrundbeleuchtung einschalten."},
		{ L"Turning backlights off.", L"Hintergrundbeleuchtung ausschalten."},
		{ L"This operation is not supported on this system.", L"Dieser Vorgang wird auf diesem System nicht unterstützt." },
		{ L"Playing Inbuilt Keyboard animation...", L"Animation der integrierten Tastatur wird abgespielt..." },
		{ L"Setting user provided colour...", L"Vom Benutzer bereitgestellte Farbe wird festgelegt..." },
		{ L"This operation is not supported on this keyboard type.", L"Dieser Vorgang wird von diesem Tastaturtyp nicht unterstützt."},
		{ L"Invalid argument: Must specify 3 hexadecimal colour values.", L"Ungültiges Argument: Es müssen 3 hexadezimale Farbwerte angegeben werden." },
		{ L"Setting user provided zone colours...", L"Festlegen der vom Benutzer bereitgestellten Zonenfarben..." },
		{ L"Setting user provided lightbar colour...", L"Setze die vom Benutzer bereitgestellte Farbe der Lichtleiste..." },
		{ L"An invalid command was provided.", L"Es wurde ein ungültiger Befehl angegeben." },
		{ L"Exiting...", L"Beenden..." },
		{ L"Invalid inbuilt animation name was provided.", L"Es wurde ein ungültiger Name für eine integrierte Animation angegeben." },
		{ L"Invalid theme command.", L"Ungültiger Theme-Befehl." },
		{ L"Invalid animation name was provided!", L"Es wurde ein ungültiger Animationsname angegeben!" },
		{ L"Failed to parse speed input! Fallback to default speed.", L"Geschwindigkeitseingabe konnte nicht verarbeitet werden! Rückgriff auf Standardgeschwindigkeit." },
		{ L"You can only have 1 instance of this program running. Please close any other instances.", L"Dieses Programm kann nur in einer einzigen Instanz ausgeführt werden. Bitte schließen Sie alle weiteren Instanzen." },
		{ L"This system is not supported.\nPlease request for support using the following URL: https://github.com/DeviceIoControl/CppKeyboardColour/issues/new/choose.", L"Dieses System wird nicht unterstützt.\nBitte fordern Sie Unterstützung über die folgende URL an: https://github.com/DeviceIoControl/CppKeyboardColour/issues/new/choose." },
		{ L"Cannot enable hidden mode with Device monitor mode enabled.", L"Der verborgene Modus kann nicht aktiviert werden, während der Geräteüberwachungsmodus eingeschaltet ist." },
		{ L"Invalid command line. Command is: CLEVO_KeyboardColour.exe theme/inbuilt/backlight/lightbar/colour(s) [<themeName>/<hexColour>] [--once] [--speed] <speed> [--dmm] [--hide]", L"Ongeldige opdrachtregel. De opdracht is: CLEVO_KeyboardColour.exe theme/inbuilt/backlight/lightbar/colour(s) [<themeName>/<hexColour>] [--once] [--speed] <speed> [--dmm] [--hide]" },
		{ L"Cannot communicate with the requested device.", L"Es kann keine Kommunikation mit dem angeforderten Gerät hergestellt werden." },
		{ L"Failed to detect the host's RGB devices.", L"Die RGB-Geräte des Hosts konnten nicht erkannt werden." },
		{ L"Failed to detected Model ID.", L"Modell-ID konnte nicht erkannt werden." },
		{ L"\nPress ENTER to exit.", L"\nDrücken Sie die EINGABETASTE, um zu beenden." }
	};
};