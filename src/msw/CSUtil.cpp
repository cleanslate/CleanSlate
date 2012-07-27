//
//  CSUtil.cpp
//  CleanSlate
//
//  Created by Yulius Tjahjadi on 7/27/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//
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