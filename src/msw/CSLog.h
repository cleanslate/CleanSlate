#ifndef __CSLOG_H__
#define __CSLOG_H__

#ifdef DEBUG
#define CSLogDebug CSLogDebugImpl
#else
#define CSLogDebug(...) (void *)0
#endif

#define CSLogError CSLogErrorImpl
#define CSLogInfo CSLogInfoImpl

void CSLogDebugImpl(const char *fmt, ...);
void CSLogErrorImpl(const char *fmt, ...);
void CSLogInfoImpl(const char *fmt, ...);

#endif