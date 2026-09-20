#include "stdafx.h"
#include "FileUtils.h"

namespace File 
{
	bool Exists(const std::wstring& path)
	{
		const auto res = GetFileAttributesW(path.c_str());
		return res != INVALID_FILE_ATTRIBUTES && !!(res & FILE_ATTRIBUTE_NORMAL);
	}

} // namespace File