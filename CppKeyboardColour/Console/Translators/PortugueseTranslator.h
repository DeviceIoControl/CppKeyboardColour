// Created by DeviceIoControl

#pragma once
#include "ITranslator.h"
#include "../LogLevel.h"

#define PORTUGUESE_PROGRAM_NAME L"Ferramenta de Cores do Teclado CLEVO"

class PortugueseTranslator
	: public ITranslator
{
public:
	PortugueseTranslator() = default;
	~PortugueseTranslator() override = default;

	std::wstring Translate(const std::wstring& msg) override;
	std::wstring Translate(LogLevel level) override;
	bool IsCompatible(LANGID langId) const override;

private:
	std::map<std::wstring, std::wstring> m_mapping
	{
		{ RELEASE_BUILD_STRING, MAKE_RELEASE_BUILD_STRING(PORTUGUESE_PROGRAM_NAME, L"Criado por DeviceIoControl")},
		{ TEST_BUILD_STRING, MAKE_NONRELEASE_BUILD_STRING(PORTUGUESE_PROGRAM_NAME, L"Versão de teste", L"Criado por DeviceIoControl") },
		{ DEBUG_BUILD_STRING, MAKE_NONRELEASE_BUILD_STRING(PORTUGUESE_PROGRAM_NAME, L"Compilação de depuração", L"Criado por DeviceIoControl") },
		{ L"Detected Model ID: 0x%08X", L"ID do modelo detectado: 0x%08X" },
		{ L"Host Devices: %s", L"Dispositivos host: %s" },
		{ L"Keyboard Type: %s", L"Tipo de teclado: %s" },
		{ L"Model Name: %s", L"Nome do modelo: %s" },
		{ L"Device monitor mode enabled! (Performance may be affected)", L"Modo de monitoramento de dispositivo ativado! (O desempenho pode ser afetado)"},
		{ L"{%s} - Code: 0x%08X -> %s Colour: (RED: 0x%08X), (GREEN: 0x%08X), (BLUE: 0x%08X)", L"{%s} - Código: 0x%08X -> %s Cor: (VERMELHO: 0x%08X), (VERDE: 0x%08X), (AZUL: 0x%08X)"},
		{ L"Speed value out of range (1-250) - Will use default speed.", L"Valor de velocidade fora da faixa (1-250) – A velocidade padrão será utilizada."},
		{ L"Playing '%s' animation...", L"Reproduzindo a animação '%s'..."},
		{ L"'%s' animation is not supported on this system.", L"A animação '%s' não é suportada neste sistema."},
		{ L"Cannot load %s. Please ensure the DLL is within the same directory!", L"Não é possível carregar %s. Certifique-se de que a DLL esteja no mesmo diretório!" },
		{ L"Cannot load clevomof.dll.\nPlease ensure the DLL is registered correctly.", L"Não é possível carregar o arquivo clevomof.dll.\nCertifique-se de que a DLL esteja registrada corretamente."},
		{ L"Cannot load clevomof.dll.", L"Não é possível carregar clevomof.dll." },
		{ L"Cannot load clevomof.dll.\nPlease ensure the DLL is at: %s", L"Não é possível carregar clevomof.dll.\nCertifique-se de que a DLL esteja em: %s"},
		{ L"CLEVOMOF.dll is registered - Failed to access code.\nPlease restart your system and try again.", L"CLEVOMOF.dll está registrado – Falha ao acessar o código.\nReinicie o sistema e tente novamente."},
		{ L"Turning backlights on.", L"Ligando a retroiluminação."},
		{ L"Turning backlights off.", L"Desligando a retroiluminação."},
		{ L"This operation is not supported on this system.", L"Esta operação não é suportada neste sistema." },
		{ L"Playing Inbuilt Keyboard animation...", L"Reproduzindo animação do teclado integrado..." },
		{ L"Setting user provided colour...", L"Definindo a cor fornecida pelo usuário..." },
		{ L"This operation is not supported on this keyboard type.", L"Esta operação não é compatível com este tipo de teclado."},
		{ L"Invalid argument: Must specify 3 hexadecimal colour values.", L"Argumento inválido: é necessário especificar 3 valores de cor em hexadecimal." },
		{ L"Setting user provided zone colours...", L"Definindo as cores de zona fornecidas pelo usuário..." },
		{ L"Setting user provided lightbar colour...", L"Definindo a cor da barra de luz conforme especificado pelo usuário..." },
		{ L"An invalid command was provided.", L"Um comando inválido foi fornecido." },
		{ L"Exiting...", L"Saindo..." },
		{ L"Invalid inbuilt animation name was provided.", L"Foi fornecido um nome de animação nativa inválido." },
		{ L"Invalid theme command.", L"Comando de tema inválido." },
		{ L"Invalid animation name was provided!", L"Foi fornecido um nome de animação inválido!" },
		{ L"Failed to parse speed input! Fallback to default speed.", L"Falha ao analisar a entrada de velocidade! Utilizando a velocidade padrão." },
		{ L"You can only have 1 instance of this program running. Please close any other instances.", L"Você só pode ter uma instância deste programa em execução. Por favor, feche as demais instâncias." },
		{ L"This system is not supported.\nPlease request for support using the following URL: https://github.com/DeviceIoControl/CppKeyboardColour/issues/new/choose.", L"Este sistema não é suportado.\nPor favor, solicite suporte utilizando a seguinte URL: https://github.com/DeviceIoControl/CppKeyboardColour/issues/new/choose." },
		{ L"Cannot enable hidden mode with Device monitor mode enabled.", L"Não é possível ativar o modo oculto com o modo de monitoramento de dispositivo ativado." },
		{ L"Invalid command line. Command is: CLEVO_KeyboardColour.exe theme/inbuilt/backlight/lightbar/colour(s) [<themeName>/<hexColour>] [--once] [--speed] <speed> [--dmm] [--hide]", L"Linha de comando inválida. O comando é: CLEVO_KeyboardColour.exe theme/inbuilt/backlight/lightbar/colour(s) [<nomeDoTema>/<corHexadecimal>] [--once] [--speed] <velocidade> [--dmm] [--hide]" },
		{ L"Cannot communicate with the requested device.", L"Não é possível comunicar-se com o dispositivo solicitado." },
		{ L"Failed to detect the host's RGB devices.", L"Não foi possível detectar os dispositivos RGB do host." },
		{ L"Failed to detected Model ID.", L"Não foi possível detectar o ID do modelo." }
	};
};