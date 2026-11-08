// Created by DeviceIoControl

#pragma once
#include "ITranslator.h"
#include "../LogLevel.h"

class ItalianTranslator
	: public ITranslator
{
public:
	ItalianTranslator() = default;
	~ItalianTranslator() override = default;

	std::wstring Translate(const std::wstring& msg) override;
	std::wstring Translate(LogLevel level) override;

private:
	std::map<std::wstring, std::wstring> m_mapping
	{
		{ L"CLEVO Keyboard Colours Tool 1.26.XXXX (Debug Build) - Created by DeviceIoControl.", L"CLEVO Keyboard Colours Tool 1.26.XXXX (Build di debug) - Creato da DeviceIoControl."},
		{ L"Detected Model ID: 0x%08X", L"ID modello rilevato: 0x%08X" },
		{ L"Host Devices: %s", L"Dispositivi host: %s" },
		{ L"Keyboard Type: %s", L"Tipo di tastiera: %s" },
		{ L"Model Name: %s", L"Nome del modello: %s" },
		{ L"Device monitor mode enabled! (Performance may be affected)", L"Modalità monitoraggio dispositivo attivata! (Le prestazioni potrebbero risentirne)"},
		{ L"{%s} - Code: 0x%08X -> %s Colour: (RED: 0x%08X), (GREEN: 0x%08X), (BLUE: 0x%08X)", L"{%s} - Codice: 0x%08X -> %s Colore: (ROSSO: 0x%08X), (VERDE: 0x%08X), (BLU: 0x%08X)"},
		{ L"Speed value out of range (1-250) - Will use default speed.", L"Valore di velocità fuori intervallo (1-250) - Verrà utilizzata la velocità predefinita."},
		{ L"Playing '%s' animation...", L"Riproduzione dell'animazione '%s'..." },
		{ L"'%s' animation is not supported on this system.", L"L'animazione '%s' non è supportata su questo sistema."},
		{ L"Cannot load %s. Please ensure the DLL is within the same directory!", L"Impossibile caricare %s. Assicurarsi che la DLL si trovi nella stessa directory!" },
		{ L"Cannot load clevomof.dll.\nPlease ensure the DLL is registered correctly.", L"Impossibile caricare clevomof.dll.\nAssicurarsi che la DLL sia registrata correttamente."},
		{ L"Cannot load clevomof.dll.", L"Impossibile caricare clevomof.dll." },
		{ L"Cannot load clevomof.dll.\nPlease ensure the DLL is at: %s", L"Impossibile caricare clevomof.dll.\nAssicurarsi che il file DLL si trovi in: %s"},
		{ L"CLEVOMOF.dll is registered - Failed to access code.\nPlease restart your system and try again.", L"CLEVOMOF.dll è registrato - Impossibile accedere al codice.\nRiavviare il sistema e riprovare."},
		{ L"Turning backlights on.", L"Accensione della retroilluminazione." },
		{ L"Turning backlights off.", L"Spegnimento della retroilluminazione."},
		{ L"This operation is not supported on this system.", L"Questa operazione non è supportata su questo sistema." },
		{ L"Playing Inbuilt Keyboard animation...", L"Riproduzione dell'animazione della tastiera integrata..." },
		{ L"Setting user provided colour...", L"Impostazione del colore fornito dall'utente..." },
		{ L"This operation is not supported on this keyboard type.", L"Questa operazione non è supportata su questo tipo di tastiera." },
		{ L"Invalid argument: Must specify 3 hexadecimal colour values.", L"Argomento non valido: è necessario specificare 3 valori di colore esadecimali." },
		{ L"Setting user provided zone colours...", L"Impostazione dei colori delle zone forniti dall'utente..." },
		{ L"Setting user provided lightbar colour...", L"Impostazione del colore della barra luminosa specificato dall'utente..." },
		{ L"An invalid command was provided.", L"È stato fornito un comando non valido." },
		{ L"Exiting...", L"Uscita in corso..." },
		{ L"Invalid inbuilt animation name was provided.", L"È stato fornito un nome di animazione integrata non valido." },
		{ L"Invalid theme command.", L"Comando tema non valido." },
		{ L"Invalid animation name was provided!", L"È stato fornito un nome di animazione non valido!" },
		{ L"Failed to parse speed input! Fallback to default speed.", L"Impossibile analizzare il valore di velocità inserito! Ripristino della velocità predefinita." },
		{ L"You can only have 1 instance of this program running. Please close any other instances.", L"È possibile eseguire una sola istanza di questo programma. Si prega di chiudere le altre istanze." },
		{ L"This system is not supported.\nPlease request for support using the following URL: https://github.com/DeviceIoControl/CppKeyboardColour/issues/new/choose.", L"Questo sistema non è supportato.\nSi prega di richiedere assistenza utilizzando il seguente URL: https://github.com/DeviceIoControl/CppKeyboardColour/issues/new/choose." },
		{ L"Cannot enable hidden mode with Device monitor mode enabled.", L"Non è possibile attivare la modalità nascosta quando la modalità di monitoraggio del dispositivo è abilitata." },
		{ L"Invalid command line. Command is: CLEVO_KeyboardColour.exe theme/inbuilt/backlight/lightbar/colour(s) [<themeName>/<hexColour>] [--once] [--speed] <speed> [--dmm] [--hide]", L"Riga di comando non valida. Il comando è: CLEVO_KeyboardColour.exe theme/inbuilt/backlight/lightbar/colour(s) [<nomeTema>/<coloreEsadecimale>] [--once] [--speed] <velocità> [--dmm] [--hide]" },
		{ L"Cannot communicate with the requested device.", L"Impossibile comunicare con il dispositivo richiesto." },
		{ L"Failed to detect the host's devices.", L"Impossibile rilevare i dispositivi dell'host." },
		{ L"Failed to detected Model ID.", L"Impossibile rilevare l'ID modello." }
	};
};