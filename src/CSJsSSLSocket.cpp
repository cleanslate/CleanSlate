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

#include "CSJsSSLSocket.h"
#include "CSJsSocket.h"

#include "event.h"

#include <openssl/ssl.h>
#include <openssl/rand.h>

CSJsSSLSocket::CSJsSSLSocket() :
    mCTX(NULL)
{
}

CSJsSSLSocket::~CSJsSSLSocket()
{
    Close();
}

void CSJsSSLSocket::Init()
{
    SSL_load_error_strings();
    ERR_load_BIO_strings();
    SSL_library_init();
    OpenSSL_add_all_algorithms();
}

void CSJsSSLSocket::Cleanup()
{
    
}

CefRefPtr<CefV8Value> CSJsSSLSocket::CreateSocket()
{
    CSJsSSLSocket *socket = new CSJsSSLSocket();
    
    // create js object
    return socket->CreateJSObject();    
}

bool CSJsSSLSocket::Connect(const CefString &hostname, int port)
{
    Close();
    
    // don't call the open callback yet
    CefRefPtr<CefV8Value> tmpCb = mOpenCallback;
    mOpenCallback = NULL;
    bool result = CSJsSocket::Connect(hostname, port);
    mOpenCallback = tmpCb;
    
    if (!result)
        return false;

    // intialize random file
    char filename[256];
    RAND_file_name(filename, sizeof(filename) - 1);
    RAND_load_file(filename, -1);
    RAND_status();
    
    mCTX = SSL_CTX_new(SSLv3_method());
    mSSL = SSL_new(mCTX);
    SSL_set_fd(mSSL, mSocket);

    int ret = SSL_connect(mSSL);
    if (ret <= 0)
        return false;
    
    if (mOpenCallback)
    {
        CefV8ValueList args;
        CefRefPtr<CefV8Value> retval;
        CefRefPtr<CefV8Exception> exception;     
        
        args.push_back(CefV8Value::CreateObject(NULL, NULL));
        
        mOpenCallback->ExecuteFunctionWithContext(mOpenContext, NULL, args, retval, exception, false);                        
    }    

    return true;
}


void CSJsSSLSocket::Close()
{
    CSJsSocket::Close();

    if (mCTX)
    {
        SSL_CTX_free(mCTX);
        mCTX = NULL;
    }
}

int CSJsSSLSocket::Read(void *data, int size)
{
    memset(data, 0, size);
    int result = SSL_read(mSSL, data, size);
    CSLogDebug("read = %s", data);
    return result;
}

int CSJsSSLSocket::Write(const void *data, int size)
{
    CSLogDebug("write = %s", data);
    return SSL_write(mSSL, data, size);
}

