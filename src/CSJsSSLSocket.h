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

#ifndef __CSJSSSLSOCKET_H__
#define __CSJSSSLSOCKET_H__

#include <openssl/ssl.h>

#include "CSJsSocket.h"

class CSJsSSLSocket : public CSJsSocket
{
public:
    CSJsSSLSocket();
    virtual ~CSJsSSLSocket();

    static void Init();
    static void Cleanup();
    
    static CefRefPtr<CefV8Value> CreateSocket();
    
    virtual bool Connect(const CefString &hostname, int port);
    virtual void Close();
    virtual int Read(void *data, int size);
    virtual int Write(const void *data, int size);
    
private:
    SSL_CTX *mCTX;
    SSL *mSSL;
};

#endif
