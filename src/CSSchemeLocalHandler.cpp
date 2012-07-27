//
//  CSSchemeLocalHandler.cpp
//  CleanSlate
//
//  Created by Yulius Tjahjadi on 7/26/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "CSSchemeLocalHandler.h"

CSSchemeLocalHandler::CSSchemeLocalHandler() :
    mInputStream(NULL)
{
}

CSSchemeLocalHandler::~CSSchemeLocalHandler()
{
	if (mInputStream)
		fclose(mInputStream);
}

bool CSSchemeLocalHandler::ProcessRequest(CefRefPtr<CefRequest> request, CefRefPtr<CefSchemeHandlerCallback> callback)
{
	return true;
}

void CSSchemeLocalHandler::GetResponseHeaders(CefRefPtr<CefResponse> response, int64& response_length, CefString& redirectUrl)
{

}

bool CSSchemeLocalHandler::ReadResponse(void* data_out, int bytes_to_read, int& bytes_read, CefRefPtr<CefSchemeHandlerCallback> callback)
{
    return true;
}

void CSSchemeLocalHandler::Cancel()
{
    
}
