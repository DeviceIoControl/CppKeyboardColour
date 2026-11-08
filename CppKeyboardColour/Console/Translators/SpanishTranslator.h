// Created by DeviceIoControl

#pragma once
#include "ITranslator.h"
#include "../LogLevel.h"

class SpanishTranslator
	: public ITranslator
{
public:
	SpanishTranslator() = default;
	~SpanishTranslator() override = default;

	std::wstring Translate(const std::wstring& msg) override;
	std::wstring Translate(LogLevel level) override;

private:
	std::map<std::wstring, std::wstring> m_mapping
	{
		{ L"CLEVO Keyboard Colours Tool 1.26.XXXX (Debug Build) - Created by DeviceIoControl.", L"CLEVO Keyboard Colours Tool 1.26.XXXX (versión de depuración) - Creada por DeviceIoControl."},
		{ L"Detected Model ID: 0x%08X", L"ID de modelo detectado: 0x%08X" },
		{ L"Host Devices: %s", L"Dispositivos anfitriones: %s" },
		{ L"Keyboard Type: %s", L"Tipo de teclado: %s" },
		{ L"Model Name: %s", L"Nombre del modelo: %s" },
		{ L"Device monitor mode enabled! (Performance may be affected)", L"¡Modo de supervisión de dispositivo activado! (El rendimiento podría verse afectado)"},
		{ L"{%s} - Code: 0x%08X -> %s Colour: (RED: 0x%08X), (GREEN: 0x%08X), (BLUE: 0x%08X)", L"{%s} - Código: 0x%08X -> %s Color: (ROJO: 0x%08X), (VERDE: 0x%08X), (AZUL: 0x%08X)"},
		{ L"Speed value out of range (1-250) - Will use default speed.", L"Valor de velocidad fuera de rango (1-250) - Se utilizará la velocidad predeterminada."},
		{ L"Playing '%s' animation...", L"Reproduciendo la animación '%s'..." },
		{ L"'%s' animation is not supported on this system.", L"La animación '%s' no es compatible con este sistema."},
		{ L"Cannot load %s. Please ensure the DLL is within the same directory!", L"No se puede cargar %s. ¡Asegúrese de que el archivo DLL se encuentre en el mismo directorio!" },
		{ L"Cannot load clevomof.dll.\nPlease ensure the DLL is registered correctly.", L"No se puede cargar clevomof.dll.\nAsegúrese de que el archivo DLL esté registrado correctamente."},
		{ L"Cannot load clevomof.dll.", L"No se puede cargar clevomof.dll." },
		{ L"Cannot load clevomof.dll.\nPlease ensure the DLL is at: %s", L"No se puede cargar clevomof.dll.\nPor favor, asegúrese de que el archivo DLL se encuentre en: %s"},
		{ L"CLEVOMOF.dll is registered - Failed to access code.\nPlease restart your system and try again.", L"CLEVOMOF.dll está registrado; no se pudo acceder al código.\nReinicie el sistema e inténtelo de nuevo."},
		{ L"Turning backlights on.", L"Encendiendo la retroiluminación." },
		{ L"Turning backlights off.", L"Apagando la retroiluminación."},
		{ L"This operation is not supported on this system.", L"Esta operación no es compatible con este sistema." },
		{ L"Playing Inbuilt Keyboard animation...", L"Reproduciendo la animación del teclado integrado..." },
		{ L"Setting user provided colour...", L"Estableciendo el color proporcionado por el usuario..." },
		{ L"This operation is not supported on this keyboard type.", L"Esta operación no es compatible con este tipo de teclado." },
		{ L"Invalid argument: Must specify 3 hexadecimal colour values.", L"Argumento no válido: se deben especificar 3 valores de color hexadecimales." },
		{ L"Setting user provided zone colours...", L"Estableciendo los colores de zona proporcionados por el usuario..." },
		{ L"Setting user provided lightbar colour...", L"Estableciendo el color de la barra de luces indicado por el usuario..." },
		{ L"An invalid command was provided.", L"Se ha proporcionado un comando no válido." },
		{ L"Exiting...", L"Saliendo..." },
		{ L"Invalid inbuilt animation name was provided.", L"Se ha proporcionado un nombre de animación integrada no válido." },
		{ L"Invalid theme command.", L"Comando de tema no válido." },
		{ L"Invalid animation name was provided!", L"¡Se ha proporcionado un nombre de animación no válido!" },
		{ L"Failed to parse speed input! Fallback to default speed.", L"¡No se pudo analizar el valor de velocidad introducido! Se recurre a la velocidad predeterminada." },
		{ L"You can only have 1 instance of this program running. Please close any other instances.", L"Solo puede haber una instancia de este programa en ejecución. Por favor, cierra cualquier otra instancia." },
		{ L"This system is not supported.\nPlease request for support using the following URL: https://github.com/DeviceIoControl/CppKeyboardColour/issues/new/choose.", L"Este sistema no es compatible.\nPor favor, solicite asistencia a través de la siguiente URL: https://github.com/DeviceIoControl/CppKeyboardColour/issues/new/choose." },
		{ L"Cannot enable hidden mode with Device monitor mode enabled.", L"No es posible activar el modo oculto mientras el modo de supervisión del dispositivo está habilitado." },
		{ L"Invalid command line. Command is: CLEVO_KeyboardColour.exe theme/inbuilt/backlight/lightbar/colour(s) [<themeName>/<hexColour>] [--once] [--speed] <speed> [--dmm] [--hide]", L"Línea de comandos no válida. El comando es: CLEVO_KeyboardColour.exe theme/inbuilt/backlight/lightbar/colour(s) [<nombreDelTema>/<colorHexadecimal>] [--once] [--speed] <velocidad> [--dmm] [--hide]" },
		{ L"Cannot communicate with the requested device.", L"No es posible comunicarse con el dispositivo solicitado." },
		{ L"Failed to detect the host's devices.", L"No se pudieron detectar los dispositivos del host." },
		{ L"Failed to detected Model ID.", L"No se pudo detectar el ID del modelo." }
	};
};