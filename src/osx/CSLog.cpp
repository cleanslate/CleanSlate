//
//  CSLog.cpp
//  CleanSlate
//
//  Created by Yulius Tjahjadi on 7/25/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <stdio.h>
#include <stdarg.h>

void CSLogDebugImpl(const char *fmt, ...)
{
    fprintf(stdout, "DEBUG: ");
    va_list ap;
    va_start(ap, fmt);
    vfprintf(stdout, fmt, ap);
    va_end(ap);
    fprintf(stdout, "\n");

}

void CSLogErrorImpl(const char *fmt, ...)
{
    fprintf(stderr, "ERROR: ");
    va_list ap;
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
    fprintf(stderr, "\n");    
}

void CSLogInfoImpl(const char *fmt, ...)
{
    fprintf(stdout, "INFO: ");
    va_list ap;
    va_start(ap, fmt);
    vfprintf(stdout, fmt, ap);
    va_end(ap);
    fprintf(stdout, "\n");    
}
