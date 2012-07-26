//
//  CSLog.h
//  CleanSlate
//
//  Created by Yulius Tjahjadi on 7/25/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef __CSLOG_H__
#define __CSLOG_H__

#ifdef DEBUG
#define CSLogDebug CSLogDebugImpl
#else
#define CSLogDebug(...) (void *)
#endif

#define CSLogError CSLogErrorImpl
#define CSLogInfo CSLogInfoImpl

void CSLogDebugImpl(const char *fmt, ...);
void CSLogErrorImpl(const char *fmt, ...);
void CSLogInfoImpl(const char *fmt, ...);

#endif
