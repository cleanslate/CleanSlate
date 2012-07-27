//
//  CSBrowserClient.cpp
//  CleanSlate
//
//  Created by Yulius Tjahjadi on 7/25/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>

#include "include/cef_app.h"
#include "include/cef_client.h"

#include "CSBrowserClient.h"
#include "CSWindow.h"
#include "CSLog.h"
#include "CSRect.h"

static void CopyRGBA(std::vector<unsigned char> &image, const unsigned char *buffer, int width, int height, const CefRect &rect)
{
    if (image.size() != width*height*4)
        image.resize(width*height*4);
    
    for (int y = 0; y < height; y++)
    {
        unsigned char *dst = &image[y*width*4];
        const unsigned char *src = &buffer[y*width*4];
        for (int x = 0; x < width; x++)
        {
            dst[0] = src[0];
            dst[1] = src[1];
            dst[2] = src[2];
            dst[3] = src[3];
            
            dst += 4;
            src += 4;
        }
    }
}


CSBrowserClient::CSBrowserClient(CSWindow *window) :
    mWindow(window)
{
    mImage.resize(100*100);
}


CSBrowserClient::~CSBrowserClient()
{
    
}

void CSBrowserClient::OnAfterCreated(CefRefPtr<CefBrowser> browser)
{
    int width, height;
    
    mWindow->GetSize(width, height);
    CSLogInfo("OnAfterCreated: %dx%d size", width, height);
    
    mBrowser = browser;
    mBrowser->SetSize(PET_VIEW, width, height);
    
    mBrowser->SendFocusEvent(true);
}

void CSBrowserClient::OnBeforeClose(CefRefPtr<CefBrowser> browser)
{
    CSLogDebug("OnBeforeClose");    
    mBrowser = NULL;
}

void CSBrowserClient::OnLoadStart(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame)
{
    CSLogDebug("OnLoadStart"); 
}

void CSBrowserClient::OnLoadEnd(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, int httpStatusCode)
{
    
}

bool CSBrowserClient::OnLoadError(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefLoadHandler::ErrorCode errorCode, const CefString& failedUrl, CefString& errorText)
{
    return true;
}

void CSBrowserClient::OnTitleChange(CefRefPtr<CefBrowser> browser, const CefString& title)
{
    
}

bool CSBrowserClient::OnConsoleMessage(CefRefPtr<CefBrowser> browser, const CefString& message, const CefString& source, int line)
{
    return true;
}

// CefRenderHandler
bool CSBrowserClient::GetViewRect(CefRefPtr<CefBrowser> browser, CefRect& rect)
{
    return true;
}

bool CSBrowserClient::GetScreenRect(CefRefPtr<CefBrowser> browser, CefRect& rect)
{
    return true;
}

bool CSBrowserClient::GetScreenPoint(CefRefPtr<CefBrowser> browser, int viewX, int viewY, int& screenX, int& screenY)
{
    return true;
}

void CSBrowserClient::OnPopupShow(CefRefPtr<CefBrowser> browser, bool show)
{
    
}

void CSBrowserClient::OnPopupSize(CefRefPtr<CefBrowser> browser, const CefRect& rect)
{
    
}

void CSBrowserClient::OnPaint(CefRefPtr<CefBrowser> browser, CefBrowser::PaintElementType type, const CefRenderHandler::RectList& dirtyRects, const void* buffer)
{
    CSLogDebug("OnPaint()");
    
    int width, height;
    browser->GetSize(PET_VIEW, width, height);
    
    RectList::const_iterator i = dirtyRects.begin();
    for (; i != dirtyRects.end(); ++i)
    {
        const CefRect &rect = *i;
        CSLogDebug("\tRect %dx%d %dx%d", rect.x, rect.y, rect.width, rect.height);
        CopyRGBA(mImage, (unsigned char *)buffer, width, height, rect);

        CSRect csRect;
        csRect.x = rect.x;
        csRect.y = rect.y;
        csRect.width = rect.width;
        csRect.height = rect.height;
        mWindow->InvalidateRect(csRect);
    }
}

void CSBrowserClient::OnCursorChange(CefRefPtr<CefBrowser> browser, CefCursorHandle cursor)
{
    
}

CSBrowserClient::Image &CSBrowserClient::GetBrowserImage()
{
    return mImage;
}

void CSBrowserClient::GetBrowserSize(int &width, int &height)
{
    width = height = 0;
    if (mBrowser.get())
        mBrowser->GetSize(PET_VIEW, width, height);
}

