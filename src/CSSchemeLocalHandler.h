//
//  CSSchemeLocalHandler.h
//  CleanSlate
//
//  Created by Yulius Tjahjadi on 7/26/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

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
