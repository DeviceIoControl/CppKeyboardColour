#include "stdafx.h"
#include "FileUtils.h"

namespace File 
{
	bool Exists(const std::wstring& path)
	{
		return !!(GetFileAttributesW(path.c_str()) & FILE_ATTRIBUTE_NORMAL);
	}

} // namespace File