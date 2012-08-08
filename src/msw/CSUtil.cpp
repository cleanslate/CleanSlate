/* 
 *
 * Copyright 2012 Yulius Tjahjadi <yultide@yahoo.com>
 *
 * This file is part of CleanSlate.
 * 
 * CleanSlate is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * CleanSlate is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License 
 * along with CleanSlate. If not, see http://www.gnu.org/licenses/.
 *
 */

#include "CSPrecomp.h"

#include "CSUtil.h"

std::string CSUtil::GetLocalDir()
{
	// local path is the same as the executable path

	char filename[MAX_PATH];
	HMODULE hModule = GetModuleHandle(NULL);
	GetModuleFileNameA(hModule, filename, sizeof(filename));

	std::string str = filename;
	size_t pos = str.rfind(OS_PATH_SEP);
	str = str.substr(0, pos);

	return str;
}

std::string CSUtil::GetOS()
{
	return "msw";
}

bool CSUtil::Unlink(const CefString &path)
{
	return DeleteFile(path.ToWString().c_str()) == TRUE;
}
