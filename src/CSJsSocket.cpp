//
//  CSJsSocket.cpp
//  CleanSlate
//
//  Created by Yulius Tjahjadi on 7/28/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "CSPrecomp.h"

#include "CSJsSocket.h"

#include "event.h"

CSJsSocket::CSJsSocket(int socket) :
    mSocket(socket)
{
    event_set(&mEventRead, mSocket, EV_READ|EV_PERSIST, &CSJsSocket::OnReadStatic, this);
    event_add(&mEventRead, NULL);
}

CSJsSocket::~CSJsSocket()
{
    close(mSocket);
}

CefRefPtr<CefV8Value> CSJsSocket::CreateSocket(const CefString &hostname, int port)
{
    int s = socket(AF_INET, SOCK_STREAM, 0);
    struct hostent *he;
    struct sockaddr_in saddr = {0};
    
    saddr.sin_addr.s_addr = inet_addr(hostname.ToString().c_str());
    if (saddr.sin_addr.s_addr == INADDR_NONE)
    {
        he = gethostbyname(hostname.ToString().c_str());
        if (he)
            memcpy(&saddr.sin_addr.s_addr, he->h_addr_list[0], he->h_length);
    }
    
    saddr.sin_port = htons(port);
	saddr.sin_family = AF_INET;
    
    if (connect(s, (struct sockaddr *)&saddr, sizeof(saddr)) == 0)
    {
        CSJsSocket *socket = new CSJsSocket(s);
        CefRefPtr<CefV8Value> obj = CefV8Value::CreateObject(socket, NULL);
        
        // bind functions
        obj->SetValue("send", CefV8Value::CreateFunction("send", socket), V8_PROPERTY_ATTRIBUTE_READONLY);
        obj->SetValue("recv", CefV8Value::CreateFunction("recv", socket), V8_PROPERTY_ATTRIBUTE_READONLY);
        obj->SetValue("close", CefV8Value::CreateFunction("close", socket), V8_PROPERTY_ATTRIBUTE_READONLY);
        
        return obj;
    }
    
    return NULL;
}

bool CSJsSocket::Execute(const CefString& name,  CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments,  CefRefPtr<CefV8Value>& retval, CefString& exception)
{
    if (name == "send")
    {
        if (arguments.size() == 1)
        {
            std::string data = arguments[0]->GetStringValue().ToString();
            int size = send(mSocket, data.c_str(), data.size(), 0);
            retval = CefV8Value::CreateInt(size);
            return true;
        }
    }
    else if (name == "recv")
    {
        if (arguments.size() == 1)
        {
            mReadCallback = arguments[0];
            mContext = CefV8Context::GetCurrentContext();
        }
    }
    else if (name == "close")
    {
        if (arguments.size() == 1)
        {
            mCloseCallback = arguments[0];
            mContext = CefV8Context::GetCurrentContext();
        }
        else
        {
            close(mSocket);
        }
    }
    
    return false;
}

void CSJsSocket::OnRead(int fd, short ev)
{
    char buffer[1024];
    int len = recv(fd, buffer, sizeof(buffer), 0);
    if (len == 0 || len == -1)
    {
        close(fd);
		event_del(&mEventRead);
        
        // we call the close callback
        if (mCloseCallback)
        {
            CefV8ValueList args;
            CefRefPtr<CefV8Value> retval;
            CefRefPtr<CefV8Exception> exception;     
            
            args.push_back(CefV8Value::CreateInt(len));
            
            mCloseCallback->ExecuteFunctionWithContext(mContext, NULL, args, retval, exception, false);
        }
        
		return;
	}
    else
    {
        // we read something
        if (mReadCallback)
        {
            CefV8ValueList args;
            CefRefPtr<CefV8Value> retval;
            CefRefPtr<CefV8Exception> exception;     
            
            
            std::string data(buffer, len);
            args.push_back(CefV8Value::CreateString(data));
            args.push_back(CefV8Value::CreateInt(len));
            
            mReadCallback->ExecuteFunctionWithContext(mContext, NULL, args, retval, exception, false);
        }
    }
}


void CSJsSocket::OnReadStatic(int fd, short ev, void *arg)
{
    CSJsSocket *s = (CSJsSocket *)arg;
    s->OnRead(fd, ev);
}
