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
#include "CSLog.h"

static char g_str[2048];

void CSLogDebugImpl(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    wvsprintfA(g_str, fmt, ap);
    va_end(ap);
    OutputDebugStringA("DEBUG: ");
    OutputDebugStringA(g_str);
	OutputDebugStringA("\n");
}

void CSLogErrorImpl(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    wvsprintfA(g_str, fmt, ap);
    va_end(ap);
    OutputDebugStringA("ERROR: ");
    OutputDebugStringA(g_str);
	OutputDebugStringA("\n");
}

void CSLogInfoImpl(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    wvsprintfA(g_str, fmt, ap);
    va_end(ap);
    OutputDebugStringA("INFO: ");
    OutputDebugStringA(g_str);
	OutputDebugStringA("\n"); 
}
