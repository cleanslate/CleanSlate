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
