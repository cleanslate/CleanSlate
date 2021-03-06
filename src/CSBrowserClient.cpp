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

#include "include/cef_app.h"
#include "include/cef_client.h"

#include "CSBrowserClient.h"
#include "CSWindow.h"
#include "CSLog.h"
#include "CSRect.h"


// javascript modules
#include "CSJsUi.h"
#include "CSJsSys.h"
#include "CSJsNet.h"
#include "CSJsApp.h"


CSBrowserClient::CSBrowserClient(CSWindow *window) :
    mWindow(window)
{

}

CSBrowserClient::~CSBrowserClient()
{
    JSModules::iterator iter;
    for (iter = mJSModules.begin(); iter != mJSModules.end(); iter++)
    {
        delete (*iter).second;
    }
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
    
    // destroy the window
    mWindow->Destroy();
}

void CSBrowserClient::OnLoadStart(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame)
{
    CSLogDebug("OnLoadStart"); 
}

void CSBrowserClient::OnLoadEnd(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, int httpStatusCode)
{
    CSLogDebug("OnLoadEnd"); 
}

bool CSBrowserClient::OnLoadError(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefLoadHandler::ErrorCode errorCode, const CefString& failedUrl, CefString& errorText)
{
    CSLogError("code:%d url:%s error:%s", errorCode, failedUrl.ToString().c_str(), errorText.ToString().c_str());
    return true;
}

void CSBrowserClient::OnTitleChange(CefRefPtr<CefBrowser> browser, const CefString& title)
{
    CSLogInfo("OnTitleChange() - %s", title.ToString().c_str());
}

bool CSBrowserClient::OnConsoleMessage(CefRefPtr<CefBrowser> browser, const CefString& message, const CefString& source, int line)
{
    CSLogInfo("%s:%d - %s", source.ToString().c_str(), line, message.ToString().c_str());
    return true;
}

// CefRenderHandler
bool CSBrowserClient::GetViewRect(CefRefPtr<CefBrowser> browser, CefRect& rect)
{
    CSRect csRect;
    mWindow->GetViewRect(csRect);
    
    rect.x = csRect.x;
    rect.y = csRect.y;
    rect.width = csRect.width;
    rect.height = csRect.height;
    
    return true;
}

bool CSBrowserClient::GetScreenRect(CefRefPtr<CefBrowser> browser, CefRect& rect)
{
    return GetViewRect(browser, rect);
}

bool CSBrowserClient::GetScreenPoint(CefRefPtr<CefBrowser> browser, int viewX, int viewY, int& screenX, int& screenY)
{
    mWindow->GetScreenPoint(viewX, viewY, screenX, screenY);
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
    //CSLogDebug("OnPaint()");
    
    int width, height;
    browser->GetSize(PET_VIEW, width, height);
    
    RectList::const_iterator i = dirtyRects.begin();
    for (; i != dirtyRects.end(); ++i)
    {
        const CefRect &rect = *i;
        //CSLogDebug("\tRect %dx%d %dx%d", rect.x, rect.y, rect.width, rect.height);
		CSRect csRect = { rect.x, rect.y, rect.width, rect.height };
 
		mWindow->UpdateRect((unsigned char *)buffer, width, height, csRect); 
        mWindow->InvalidateRect(csRect);
    }
}

void CSBrowserClient::OnCursorChange(CefRefPtr<CefBrowser> browser, CefCursorHandle cursor)
{
    mWindow->SetCursor(cursor);
}

void CSBrowserClient::OnContextCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context)
{
	mJS = context;
    JSModules::iterator iter;
    
    // register any javascript plugins
    CefRefPtr<CefV8Value> windowObject = context->GetGlobal();
	{
        iter = mJSModules.find("ui");
        if (iter == mJSModules.end())
        {
            CSJsUi *js = new CSJsUi(mWindow);
            js->Register(windowObject);
            mJSModules["ui"] = js;
        }
        else
        {
            CSJsUi *js = (CSJsUi *)(*iter).second;
            js->Register(windowObject);
        }
	}
    
    {
        iter = mJSModules.find("sys");
        if (iter == mJSModules.end())
        {
            CSJsSys *js = new CSJsSys(mWindow);
            js->Register(windowObject);
            mJSModules["sys"] = js;
        }
        else
        {
            CSJsSys *js = (CSJsSys *)(*iter).second;
            js->Register(windowObject);
        }
    }
    
    {
        iter = mJSModules.find("net");
        if (iter == mJSModules.end())
        {
            CSJsNet *js = new CSJsNet(mWindow);
            js->Register(windowObject);
            mJSModules["net"] = js;
        }
        else
        {
            CSJsNet *js = (CSJsNet *)(*iter).second;
            js->Register(windowObject);            
        }
    }
    
    {
        iter = mJSModules.find("app");
        if (iter == mJSModules.end())
        {
            CSJsApp *js = new CSJsApp(mWindow);
            js->Register(windowObject);
            mJSModules["app"] = js;
        }
        else
        {
            CSJsApp *js = (CSJsApp *)(*iter).second;
            js->Register(windowObject);            
        }
    }
    
}

void CSBrowserClient::OnContextReleased(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context)
{
	mJS = NULL;
}

void CSBrowserClient::GetBrowserSize(int &width, int &height)
{
    width = height = 0;
    if (mBrowser.get())
        mBrowser->GetSize(PET_VIEW, width, height);
}

void CSBrowserClient::SetBrowserSize(int width, int height)
{
    if (mBrowser.get())
	{
        mBrowser->SetSize(PET_VIEW, width, height);
		//CefRect dirtyRect(0, 0, width, height);
		//mBrowser->Invalidate(dirtyRect);
	}
}

