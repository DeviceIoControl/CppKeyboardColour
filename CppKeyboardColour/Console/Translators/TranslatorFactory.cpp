// Created by DeviceIoControl

#include "stdafx.h"
#include "TranslatorFactory.h"
#include "EnglishTranslator.h"

std::unique_ptr<ITranslator> TranslatorFactory::Create(LANGID langId)
{	
	// switch (langId)
	// {
	// 
	// 
	// }

	return std::make_unique<EnglishTranslator>();
}