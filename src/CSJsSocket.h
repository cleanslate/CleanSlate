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

#ifndef __CSJSSOCKET_H__
#define __CSJSSOCKET_H__

class CSJsSocket : public CefV8Handler
{
public:
    CSJsSocket(int socket);
    virtual ~CSJsSocket();
    
    static CefRefPtr<CefV8Value> CreateSocket(const CefString &hostname, int port);
    
    virtual bool Execute(const CefString& name,  CefRefPtr<CefV8Value> object, 
                         const CefV8ValueList& arguments,  CefRefPtr<CefV8Value>& retval, CefString& exception);
private:
    int mSocket;
    CefV8ValueList mRecvCallback;
    struct event mEventRead;
    CefRefPtr<CefV8Value> mReadCallback;
    CefRefPtr<CefV8Value> mCloseCallback;
    CefRefPtr<CefV8Context> mContext;
    
    void OnRead(int fd, short ev);
    static void OnReadStatic(int fd, short ev, void *arg);
    
    IMPLEMENT_REFCOUNTING(CSJsSocket);
};


#endif
