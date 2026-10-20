#pragma once

#include "ITranslator.h"

class TranslatorFactory 
{
public:
	TranslatorFactory() = default;
	~TranslatorFactory() = default;

	std::unique_ptr<ITranslator> Create(LANGID langId);
};