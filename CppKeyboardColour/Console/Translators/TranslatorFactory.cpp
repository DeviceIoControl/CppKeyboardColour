// Created by DeviceIoControl

#include "stdafx.h"
#include "TranslatorFactory.h"
#include "EnglishTranslator.h"

std::unique_ptr<ITranslator> TranslatorFactory::Create(LANGID langId)
{	
	switch (langId)
	{
	case MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US):
	case MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_UK):
		return std::make_unique<EnglishTranslator>();

	}

	return std::make_unique<EnglishTranslator>();
}