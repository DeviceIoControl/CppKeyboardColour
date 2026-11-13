// Created by DeviceIoControl

#pragma once
#include "ITranslator.h"
#include "../LogLevel.h"

class SwedishTranslator
	: public ITranslator
{
public:
	SwedishTranslator() = default;
	~SwedishTranslator() override = default;

	std::wstring Translate(const std::wstring& msg) override;
	std::wstring Translate(LogLevel level) override;
	bool IsCompatible(LANGID langId) const override;

private:
	std::map<std::wstring, std::wstring> m_mapping
	{
		{ RELEASE_BUILD_STRING, L"" },
		{ TEST_BUILD_STRING, L"CLEVO Keyboard Colours Tool 1.26.XXXX (testversion) – skapad av DeviceIoControl." },
		{ DEBUG_BUILD_STRING, L"CLEVO Keyboard Colours Tool 1.26.XXXX (felsökningsversion) – Skapad av DeviceIoControl."},
		{ L"Detected Model ID: 0x%08X", L"Identifierat modell-ID: 0x%08X" },
		{ L"Host Devices: %s", L"Värdenheter: %s" },
		{ L"Keyboard Type: %s", L"Tangentbordstyp: %s" },
		{ L"Model Name: %s", L"Modellnamn: %s" },
		{ L"Device monitor mode enabled! (Performance may be affected)", L"Enhetsövervakningsläge aktiverat! (Prestandan kan påverkas)"},
		{ L"{%s} - Code: 0x%08X -> %s Colour: (RED: 0x%08X), (GREEN: 0x%08X), (BLUE: 0x%08X)", L"{%s} – Kod: 0x%08X -> %s Färg: (RÖD: 0x%08X), (GRÖN: 0x%08X), (BLÅ: 0x%08X)"},
		{ L"Speed value out of range (1-250) - Will use default speed.", L"Hastighetsvärdet ligger utanför intervallet (1–250) – standardhastighet används."},
		{ L"Playing '%s' animation...", L"Spelar upp animationen ”%s”..."},
		{ L"'%s' animation is not supported on this system.", L"Animeringen ”%s” stöds inte på det här systemet."},
		{ L"Cannot load %s. Please ensure the DLL is within the same directory!", L"Kan inte läsa in %s. Se till att DLL-filen finns i samma mapp!" },
		{ L"Cannot load clevomof.dll.\nPlease ensure the DLL is registered correctly.", L"Kan inte läsa in clevomof.dll. Se till att DLL-filen är korrekt registrerad."},
		{ L"Cannot load clevomof.dll.", L"Kan inte läsa in clevomof.dll." },
		{ L"Cannot load clevomof.dll.\nPlease ensure the DLL is at: %s", L"Kan inte läsa in clevomof.dll.\nKontrollera att DLL-filen finns på: %s"},
		{ L"CLEVOMOF.dll is registered - Failed to access code.\nPlease restart your system and try again.", L"CLEVOMOF.dll är registrerad – Det gick inte att komma åt koden.\nStarta om systemet och försök igen."},
		{ L"Turning backlights on.", L"Slår på bakgrundsbelysningen."},
		{ L"Turning backlights off.", L"Stänger av bakgrundsbelysningen."},
		{ L"This operation is not supported on this system.", L"Denna åtgärd stöds inte på detta system." },
		{ L"Playing Inbuilt Keyboard animation...", L"Spelar upp animering för inbyggt tangentbord..." },
		{ L"Setting user provided colour...", L"Ställer in färg som angetts av användaren..." },
		{ L"This operation is not supported on this keyboard type.", L"Denna åtgärd stöds inte på den här tangentbordstypen."},
		{ L"Invalid argument: Must specify 3 hexadecimal colour values.", L"Ogiltigt argument: Måste ange 3 hexadecimala färgvärden." },
		{ L"Setting user provided zone colours...", L"Ställer in zonfärger som angetts av användaren..." },
		{ L"Setting user provided lightbar colour...", L"Ställer in den av användaren angivna färgen för ljuslisten..." },
		{ L"An invalid command was provided.", L"Ett ogiltigt kommando angavs." },
		{ L"Exiting...", L"Avslutar..." },
		{ L"Invalid inbuilt animation name was provided.", L"Ett ogiltigt namn på en inbyggd animation angavs." },
		{ L"Invalid theme command.", L"Ogiltigt temakommando." },
		{ L"Invalid animation name was provided!", L"Ett ogiltigt namn på en animation angavs!" },
		{ L"Failed to parse speed input! Fallback to default speed.", L"Kunde inte tolka hastighetsindata! Återgår till standardhastighet." },
		{ L"You can only have 1 instance of this program running. Please close any other instances.", L"Du kan bara ha en instans av det här programmet igång. Stäng eventuella andra instanser." },
		{ L"This system is not supported.\nPlease request for support using the following URL: https://github.com/DeviceIoControl/CppKeyboardColour/issues/new/choose.", L"Detta system stöds inte.\nVänligen be om support via följande URL: https://github.com/DeviceIoControl/CppKeyboardColour/issues/new/choose." },
		{ L"Cannot enable hidden mode with Device monitor mode enabled.", L"Cannot enable hidden mode with Device monitor mode enabled." },
		{ L"Invalid command line. Command is: CLEVO_KeyboardColour.exe theme/inbuilt/backlight/lightbar/colour(s) [<themeName>/<hexColour>] [--once] [--speed] <speed> [--dmm] [--hide]", L"Ogiltig kommandorad. Kommandot är: CLEVO_KeyboardColour.exe theme/inbuilt/backlight/lightbar/colour(s) [<temanamn>/<hex-färg>] [--once] [--speed] <hastighet> [--dmm] [--hide]" },
		{ L"Cannot communicate with the requested device.", L"Det går inte att kommunicera med den begärda enheten." },
		{ L"Failed to detect the host's RGB devices.", L"Det gick inte att identifiera värddatorns RGB-enheter." },
		{ L"Failed to detected Model ID.", L"Kunde inte identifiera modell-ID." }
	};
};