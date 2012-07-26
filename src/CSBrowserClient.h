//
//  CSBrowserClient.h
//  CleanSlate
//
//  Created by Yulius Tjahjadi on 7/25/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef __CSBROWSERCLIENT_H__
#define __CSBROWSERCLIENT_H__

class CSWindow;

class CSBrowserClient : public CefClient,
                        public CefLifeSpanHandler,
                        public CefLoadHandler,
                        public CefRequestHandler,
                        public CefDisplayHandler,
                        public CefRenderHandler,
                        public CefV8ContextHandler
{
public:
    CSBrowserClient(CSWindow *window);
    virtual ~CSBrowserClient();
    
    // CefClient methods
    virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() { return this; }
    virtual CefRefPtr<CefLoadHandler> GetLoadHandler() { return this; }
    virtual CefRefPtr<CefRequestHandler> GetRequestHandler()  { return this; }
    virtual CefRefPtr<CefDisplayHandler> GetDisplayHandler()  { return this; }
    virtual CefRefPtr<CefRenderHandler> GetRenderHandler()  { return this; }
    virtual CefRefPtr<CefV8ContextHandler> GetV8ContextHandler() { return this; }

    // CefLifeSpanHandler
    virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser);
    virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser);

    virtual void OnLoadStart(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame);
    virtual void OnLoadEnd(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, int httpStatusCode);
    virtual bool OnLoadError(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, ErrorCode errorCode, const CefString& failedUrl, CefString& errorText); 
    
    // CefDisplayHandler
    virtual void OnTitleChange(CefRefPtr<CefBrowser> browser, const CefString& title);
    virtual bool OnConsoleMessage(CefRefPtr<CefBrowser> browser, const CefString& message, const CefString& source, int line);
    
    // CefRenderHandler
    virtual bool GetViewRect(CefRefPtr<CefBrowser> browser, CefRect& rect);
    virtual bool GetScreenRect(CefRefPtr<CefBrowser> browser, CefRect& rect);
    virtual bool GetScreenPoint(CefRefPtr<CefBrowser> browser, int viewX, int viewY, int& screenX, int& screenY);
    virtual void OnPopupShow(CefRefPtr<CefBrowser> browser, bool show);
    virtual void OnPopupSize(CefRefPtr<CefBrowser> browser, const CefRect& rect);
    virtual void OnPaint(CefRefPtr<CefBrowser> browser,  PaintElementType type, const RectList& dirtyRects, const void* buffer);
    virtual void OnCursorChange(CefRefPtr<CefBrowser> browser, CefCursorHandle cursor);
    
    // getters
    typedef std::vector<unsigned char> Image;    
    Image& GetBrowserImage();
    void GetBrowserSize(int &width, int &height);
    void SetBrowserSize(int width, int height);
    CefRefPtr<CefBrowser> GetBrowser() { return mBrowser; }

private:
    CefRefPtr<CefBrowser> mBrowser;
    CefRefPtr<CefV8Context> mJS;
    CSWindow *mWindow;
    
    Image mImage;
    //JSPluginUI *mPluginUI;

    IMPLEMENT_REFCOUNTING(CSBrowserClient);
};

#endif
