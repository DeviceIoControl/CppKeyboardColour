// Created by DeviceIoControl

#pragma once
#include "ITranslator.h"
#include "../LogLevel.h"

#define DUTCH_PROGRAM_NAME L"CLEVO-toetsenkleurentool"

class DutchTranslator
	: public ITranslator
{
public:
	DutchTranslator() = default;
	~DutchTranslator() override = default;

	std::wstring Translate(const std::wstring& msg) override;
	std::wstring Translate(LogLevel level) override;
	bool IsCompatible(LANGID langId) const override;

private:
	std::unordered_map<std::wstring, std::wstring> m_mapping
	{
		{ RELEASE_BUILD_STRING, MAKE_RELEASE_BUILD_STRING(DUTCH_PROGRAM_NAME, L"Gemaakt door DeviceIoControl.")},
		{ TEST_BUILD_STRING, MAKE_NONRELEASE_BUILD_STRING(DUTCH_PROGRAM_NAME, L"Testversie", L"Gemaakt door DeviceIoControl.") },
		{ DEBUG_BUILD_STRING, MAKE_NONRELEASE_BUILD_STRING(DUTCH_PROGRAM_NAME, L"Debug-versie", L"Gemaakt door DeviceIoControl.") },
		{ L"Detected Model ID: 0x%08X", L"Gedetecteerde model-ID: 0x%08X" },
		{ L"Host Devices: %s", L"Hostapparaten: %s" },
		{ L"Keyboard Type: %s", L"Toetsenbordtype: %s" },
		{ L"Model Name: %s", L"Modelnaam: %s" },
		{ L"Custom speed: %0.f%%\n", L"Aangepaste snelheid: %0.f%%\n" },
		{ L"Device monitor mode enabled! (Performance may be affected)", L"Apparaatbewakingsmodus ingeschakeld! (Prestaties kunnen hierdoor worden beïnvloed)"},
		{ L"{%s} - Code: 0x%08X -> %s Colour: (RED: 0x%08X), (GREEN: 0x%08X), (BLUE: 0x%08X)", L"{%s} - Code: 0x%08X -> %s Kleur: (ROOD: 0x%08X), (GROEN: 0x%08X), (BLAUW: 0x%08X)"},
		{ L"Speed value out of range (1-250) - Will use default speed.", L"Snelheidswaarde buiten bereik (1-250) – Standaardsnelheid wordt gebruikt."},
		{ L"Playing '%s' animation...", L"Animatie '%s' wordt afgespeeld..."},
		{ L"'%s' animation is not supported on this system.", L"Animatie '%s' wordt op dit systeem niet ondersteund."},
		{ L"Cannot load %s. Please ensure the DLL is within the same directory!", L"Kan %s niet laden. Zorg ervoor dat het DLL-bestand zich in dezelfde map bevindt!" },
		{ L"Cannot load clevomof.dll.\nPlease ensure the DLL is registered correctly.", L"Kan clevomof.dll niet laden.\nZorg ervoor dat het DLL-bestand correct is geregistreerd."},
		{ L"Cannot load clevomof.dll.", L"Kan clevomof.dll niet laden." },
		{ L"Cannot load clevomof.dll.\nPlease ensure the DLL is at: %s", L"Kan clevomof.dll niet laden.\nZorg ervoor dat het DLL-bestand zich bevindt op: %s"},
		{ L"CLEVOMOF.dll is registered - Failed to access code.\nPlease restart your system and try again.", L"CLEVOMOF.dll is geregistreerd - Toegang tot code mislukt.\nStart uw systeem opnieuw op en probeer het opnieuw."},
		{ L"Turning backlights on.", L"Achtergrondverlichting inschakelen."},
		{ L"Turning backlights off.", L"Achtergrondverlichting uitschakelen."},
		{ L"This operation is not supported on this system.", L"Deze bewerking wordt op dit systeem niet ondersteund." },
		{ L"Playing Inbuilt Keyboard animation...", L"Animatie van ingebouwd toetsenbord wordt afgespeeld..." },
		{ L"Setting user provided colour...", L"Kleur ingesteld door gebruiker..." },
		{ L"This operation is not supported on this keyboard type.", L"Deze bewerking wordt op dit type toetsenbord niet ondersteund."},
		{ L"Invalid argument: Must specify 3 hexadecimal colour values.", L"Ongeldig argument: Er moeten 3 hexadecimale kleurwaarden worden opgegeven." },
		{ L"Setting user provided zone colours...", L"Door de gebruiker opgegeven zonekleuren instellen..." },
		{ L"Setting user provided lightbar colour...", L"Kleur van de lichtbalk instellen zoals opgegeven door de gebruiker..." },
		{ L"An invalid command was provided.", L"Er is een ongeldig commando opgegeven." },
		{ L"Exiting...", L"Afsluiten..." },
		{ L"Invalid inbuilt animation name was provided.", L"Er is een ongeldige naam voor een ingebouwde animatie opgegeven." },
		{ L"Invalid theme command.", L"Ongeldig thema-commando." },
		{ L"Invalid animation name was provided!", L"Er is een ongeldige animatienaam opgegeven!" },
		{ L"Failed to parse speed input! Fallback to default speed.", L"Kon de snelheidsinvoer niet verwerken! Er wordt teruggevallen op de standaardsnelheid." },
		{ L"You can only have 1 instance of this program running. Please close any other instances.", L"Er kan slechts één exemplaar van dit programma tegelijk worden uitgevoerd. Sluit eventuele andere exemplaren af." },
		{ L"This system is not supported.\nPlease request for support using the following URL: https://github.com/DeviceIoControl/CppKeyboardColour/issues/new/choose.", L"Dit systeem wordt niet ondersteund.\nVraag om ondersteuning via de volgende URL: https://github.com/DeviceIoControl/CppKeyboardColour/issues/new/choose." },
		{ L"Cannot enable hidden mode with Device monitor mode enabled.", L"De verborgen modus kan niet worden ingeschakeld wanneer de apparaatmonitor-modus is geactiveerd." },
		{ L"Invalid command line. Command is: CLEVO_KeyboardColour.exe theme/inbuilt/backlight/lightbar/colour(s) [<themeName>/<hexColour>] [--once] [--speed] <speed> [--dmm] [--hide]", L"Ongeldige opdrachtregel. De opdracht is: CLEVO_KeyboardColour.exe theme/inbuilt/backlight/lightbar/colour(s) [<themeName>/<hexColour>] [--once] [--speed] <speed> [--dmm] [--hide]" },
		{ L"Cannot communicate with the requested device.", L"Kan niet communiceren met het gevraagde apparaat." },
		{ L"Failed to detect the host's RGB devices.", L"De RGB-apparaten van de host konden niet worden gedetecteerd." },
		{ L"Failed to detected Model ID.", L"Model-ID niet gedetecteerd." },
		{ L"\nPress ENTER to exit.", L"\nDruk op ENTER om af te sluiten." },
		{ L"Device monitor mode is not configured correctly! Fallback to default mode.", L"De apparaatmonitor-modus is niet correct geconfigureerd! Er wordt teruggevallen op de standaardmodus." },
		{ L"{%s} - %s failed with error status: 0x%08x.", L"{%s} - %s mislukt met foutstatus: 0x%08x." }
	};
};