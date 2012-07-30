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

#ifndef __CSSCHEMEFLOCALHANDLER_H__
#define __CSSCHEMEFLOCALHANDLER_H__

#define LOCAL_SCHEME "local"

class CSSchemeLocalHandler : public CefSchemeHandler
{
public:
    CSSchemeLocalHandler();
    ~CSSchemeLocalHandler();
    
    virtual bool ProcessRequest(CefRefPtr<CefRequest> request, CefRefPtr<CefSchemeHandlerCallback> callback);
    virtual void GetResponseHeaders(CefRefPtr<CefResponse> response, int64& response_length, CefString& redirectUrl);
    virtual bool ReadResponse(void* data_out, int bytes_to_read, int& bytes_read, CefRefPtr<CefSchemeHandlerCallback> callback);
    virtual void Cancel();
    
    IMPLEMENT_REFCOUNTING(UIBrowserSchemeHandler);
    
private:
    FILE *mFile;
    std::string mMimeType;
    
    std::string GetMimeType(const std::string &ext);
};



#endif
