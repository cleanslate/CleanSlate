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
#include "CSSchemeLocalHandler.h"
#include "CSUtil.h"

CSSchemeLocalHandler::CSSchemeLocalHandler() :
    mFile(NULL)
{
}

CSSchemeLocalHandler::~CSSchemeLocalHandler()
{
	if (mFile)
		fclose(mFile);
}

bool CSSchemeLocalHandler::ProcessRequest(CefRefPtr<CefRequest> request, CefRefPtr<CefSchemeHandlerCallback> callback)
{
    std::string url = request->GetURL().ToString();
    
	// scheme is local://
    std::string scheme = std::string(LOCAL_SCHEME).append("://file");
    std::string path = url.substr(scheme.size());
    path = CSUtil::GetLocalDir().append(OS_PATH_SEP).append(path);
    
	CSLogDebug("Loading file: %s", path.c_str());
    mFile = fopen(path.c_str(), "r");
	if (!mFile)
		return false;
    
    size_t pos = path.rfind(".");
    std::string ext = path.substr(pos+1);
    
    mMimeType = GetMimeType(ext);

	callback->HeadersAvailable();
    
	return true;
}

void CSSchemeLocalHandler::GetResponseHeaders(CefRefPtr<CefResponse> response, int64& response_length, CefString& redirectUrl)
{
    if (!mFile)
    {
        response->SetStatus(404);
        return;
    }
    
	response->SetMimeType(mMimeType);
    response->SetStatus(200);
    
	// update the headers
	CefResponse::HeaderMap header;
	response->GetHeaderMap(header);
	header.insert(std::pair<CefString, CefString>("Cache-Control", "no-cache"));
	response->SetHeaderMap(header);
    
    // Set the resulting response length
    long pos = ftell(mFile);
    fseek(mFile, 0, SEEK_END);
    response_length = ftell(mFile);
    fseek(mFile, pos, SEEK_SET);
}

bool CSSchemeLocalHandler::ReadResponse(void* data_out, int bytes_to_read, int& bytes_read, CefRefPtr<CefSchemeHandlerCallback> callback)
{
    if (!mFile)
		return false;
    
	bytes_read = fread(data_out, 1, bytes_to_read, mFile);
	return bytes_read > 0;
}

void CSSchemeLocalHandler::Cancel()
{
    if (mFile)
    {
        fclose(mFile);
        mFile = NULL;		
    }
}

std::string CSSchemeLocalHandler::GetMimeType(const std::string &ext)
{
    if (ext == "html")
        return "text/html";
    else if (ext == "css")
        return "text/css";
    else if (ext == "js")
        return "text/javascript";
    else if (ext == "jpeg" || ext == "jpg")
        return "image/jpeg";
    else if (ext == "gif")
        return "image/gif";
    else if (ext == "png")
        return "image/png";
    else if (ext == "bmp")
        return "image/bmp";
    else
        return "application/octet-stream";
}
