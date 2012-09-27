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

CefRefPtr<CefV8Value> CSJsSSLSocket::CreateSocket(const CefString &hostname, int port)
{
    CSJsSSLSocket *socket = new CSJsSSLSocket();
    bool result = socket->Open(hostname, port);
    if (!result)
    {
        delete socket;
        return NULL;
    }
    
    // bind functions
    CefRefPtr<CefV8Value> obj = CefV8Value::CreateObject(socket, NULL);
    
    obj->SetValue("send", CefV8Value::CreateFunction("send", socket), V8_PROPERTY_ATTRIBUTE_READONLY);
    obj->SetValue("recv", CefV8Value::CreateFunction("recv", socket), V8_PROPERTY_ATTRIBUTE_READONLY);
    obj->SetValue("close", CefV8Value::CreateFunction("close", socket), V8_PROPERTY_ATTRIBUTE_READONLY);
    
    return obj;
}

bool CSJsSSLSocket::Open(const CefString &hostname, int port)
{
    Close();
    
    bool result = CSJsSocket::Open(hostname, port);
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
    return SSL_read(mSSL, data, size);
}

int CSJsSSLSocket::Write(const void *data, int size)
{
    return SSL_write(mSSL, data, size);
}

