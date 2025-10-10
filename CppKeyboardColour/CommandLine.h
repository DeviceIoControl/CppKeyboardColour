#pragma once

#include "stdafx.h"
#include <string>
#include <vector>
#include <algorithm>

class CommandLine
{
public:
	// Récupère tous les arguments de ligne de commande dans un vecteur de chaînes.
	static std::vector<std::wstring> GetCommandLines(size_t argc, const wchar_t** argv)
	{
		std::vector<std::wstring> cmdLines{};

		for (size_t i = 1; i < argc; ++i)
		{
			cmdLines.emplace_back(argv[i]);
		}

		return cmdLines;
	}

	// Vérifie si un argument donné est présent dans la ligne de commande.
	static bool Contains(const std::wstring& toFind, const std::vector<std::wstring>& cmdlines)
	{
		return std::find_if(cmdlines.cbegin(), cmdlines.cend(), [&toFind](const auto& cmdLine) {
			return _wcsicmp(cmdLine.c_str(), toFind.c_str()) == 0;
			}) != cmdlines.cend();
	}

	// Récupère la valeur d'un argument. Renvoie une chaîne vide si l'argument ou sa valeur n'est pas trouvé.
	static std::wstring GetArgumentValue(const std::wstring& name, const std::vector<std::wstring>& cmdLines)
	{
		auto it = std::find_if(cmdLines.cbegin(), cmdLines.cend(), [&name](const auto& cmdLine) {
			return _wcsicmp(cmdLine.c_str(), name.c_str()) == 0;
			});

		if (it != cmdLines.cend() && std::next(it) != cmdLines.cend())
		{
			return *std::next(it);
		}

		return L"";
	}
};