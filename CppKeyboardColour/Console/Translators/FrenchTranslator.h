// Created by DeviceIoControl

#pragma once
#include "ITranslator.h"
#include "../LogLevel.h"

#define FRENCH_PROGRAM_NAME L"Outil de gestion des couleurs du clavier CLEVO"

class FrenchTranslator
	: public ITranslator
{
public:
	FrenchTranslator() = default;
	~FrenchTranslator() override = default;

	std::wstring Translate(const std::wstring& msg) override;
	std::wstring Translate(LogLevel level) override;
	bool IsCompatible(LANGID langId) const override;

private:
	std::map<std::wstring, std::wstring> m_mapping
	{
		{ RELEASE_BUILD_STRING, MAKE_RELEASE_BUILD_STRING(FRENCH_PROGRAM_NAME, L"Créé par DeviceIoControl.") },
		{ TEST_BUILD_STRING, MAKE_NONRELEASE_BUILD_STRING(FRENCH_PROGRAM_NAME, L"version de test" , L"Créé par DeviceIoControl.")},
		{ DEBUG_BUILD_STRING, MAKE_NONRELEASE_BUILD_STRING(FRENCH_PROGRAM_NAME, L"version de débogage" , L"Créé par DeviceIoControl.")},
		{ L"Detected Model ID: 0x%08X", L"ID du modèle détecté: 0x%08X" },
		{ L"Host Devices: %s", L"Appareils hôtes: %s" },
		{ L"Keyboard Type: %s", L"Type de clavier: %s" },
		{ L"Model Name: %s", L"Nom du modèle : %s" },
		{ L"Custom speed: %0.f%%\n", L"Vitesse personnalisée: %0.f%%\n" },
		{ L"Device monitor mode enabled! (Performance may be affected)", L"Mode de surveillance de l'appareil activé ! (Les performances peuvent en être affectées)"},
		{ L"{%s} - Code: 0x%08X -> %s Colour: (RED: 0x%08X), (GREEN: 0x%08X), (BLUE: 0x%08X)", L"{%s} - Code : 0x%08X -> %s Couleur : (ROUGE : 0x%08X), (VERT : 0x%08X), (BLEU : 0x%08X)"},
		{ L"Speed value out of range (1-250) - Will use default speed.", L"Valeur de vitesse hors plage (1-250) – La vitesse par défaut sera utilisée." },
		{ L"Playing '%s' animation...", L"Lecture de l’animation '%s'..."},
		{ L"'%s' animation is not supported on this system.", L"L’animation '%s' n’est pas prise en charge sur ce système."},
		{ L"Cannot load %s. Please ensure the DLL is within the same directory!", L"Impossible de charger %s. Veuillez vous assurer que la DLL se trouve dans le même répertoire !" },
		{ L"Cannot load clevomof.dll.\nPlease ensure the DLL is registered correctly.", L"Impossible de charger clevomof.dll.\nVeuillez vous assurer que la DLL est correctement enregistrée."},
		{ L"Cannot load clevomof.dll.", L"Impossible de charger clevomof.dll." },
		{ L"Cannot load clevomof.dll.\nPlease ensure the DLL is at: %s", L"Impossible de charger clevomof.dll. Veuillez vous assurer que le fichier DLL se trouve à l'emplacement suivant : %s"},
		{ L"CLEVOMOF.dll is registered - Failed to access code.\nPlease restart your system and try again.", L"CLEVOMOF.dll est enregistré – Échec de l’accès au code.\nVeuillez redémarrer votre système et réessayer."},
		{ L"Turning backlights on.", L"Activation du rétroéclairage."},
		{ L"Turning backlights off.", L"Désactivation des rétroéclairages."},
		{ L"This operation is not supported on this system.", L"Cette opération n’est pas prise en charge sur ce système." },
		{ L"Playing Inbuilt Keyboard animation...", L"Lecture de l'animation du clavier intégré..." },
		{ L"Setting user provided colour...", L"Définition de la couleur fournie par l’utilisateur..." },
		{ L"This operation is not supported on this keyboard type.", L"Cette opération n’est pas prise en charge sur ce type de clavier."},
		{ L"Invalid argument: Must specify 3 hexadecimal colour values.", L"Argument invalide : vous devez spécifier 3 valeurs de couleur hexadécimales." },
		{ L"Setting user provided zone colours...", L"Définition des couleurs de zone fournies par l'utilisateur..." },
		{ L"Setting user provided lightbar colour...", L"Définition de la couleur de la barre lumineuse fournie par l'utilisateur..." },
		{ L"An invalid command was provided.", L"Une commande non valide a été fournie." },
		{ L"Exiting...", L"Sortie..." },
		{ L"Invalid inbuilt animation name was provided.", L"Un nom d’animation intégrée non valide a été fourni." },
		{ L"Invalid theme command.", L"Commande de thème non valide." },
		{ L"Invalid animation name was provided!", L"Un nom d’animation invalide a été fourni!" },
		{ L"Failed to parse speed input! Fallback to default speed.", L"Échec de l'analyse de la valeur de vitesse fournie ! Utilisation de la vitesse par défaut." },
		{ L"You can only have 1 instance of this program running. Please close any other instances.", L"Une seule instance de ce programme peut être exécutée à la fois. Veuillez fermer toute autre instance." },
		{ L"This system is not supported.\nPlease request for support using the following URL: https://github.com/DeviceIoControl/CppKeyboardColour/issues/new/choose.", L"Ce système n’est pas pris en charge.\nVeuillez demander de l’aide via l’URL suivante : https://github.com/DeviceIoControl/CppKeyboardColour/issues/new/choose." },
		{ L"Cannot enable hidden mode with Device monitor mode enabled.", L"Impossible d'activer le mode masqué lorsque le mode de surveillance de l'appareil est activé." },
		{ L"Invalid command line. Command is: CLEVO_KeyboardColour.exe theme/inbuilt/backlight/lightbar/colour(s) [<themeName>/<hexColour>] [--once] [--speed] <speed> [--dmm] [--hide]", L"Ligne de commande non valide. La commande est : CLEVO_KeyboardColour.exe theme/inbuilt/backlight/lightbar/colour(s) [<nomDuThème>/<couleurHexadécimale>] [--once] [--speed] <vitesse> [--dmm] [--hide]" },
		{ L"Cannot communicate with the requested device.", L"Impossible de communiquer avec l’appareil demandé." },
		{ L"Failed to detect the host's RGB devices.", L"Échec de la détection des périphériques RGB de l'hôte." },
		{ L"Failed to detected Model ID.", L"Impossible de détecter l’identifiant du modèle." },
		{ L"\nPress ENTER to exit.", L"\nAppuyez sur ENTRÉE pour quitter." }
	};
};