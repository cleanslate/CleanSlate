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
