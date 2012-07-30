//
//  CSJsSocket.h
//  CleanSlate
//
//  Created by Yulius Tjahjadi on 7/28/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

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
