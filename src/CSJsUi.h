//
//  CSJsUi.h
//  CleanSlate
//
//  Created by Yulius Tjahjadi on 7/27/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef __CSJSUI_H__
#define __CSJSUI_H__

class CSWindow;

class CSJsUi : public CefV8Handler
{
public:
    CSJsUi(CSWindow *window);
    virtual ~CSJsUi();
    
    void Register(CefRefPtr<CefV8Value> windowObject);
    
    virtual bool Execute(const CefString& name,  CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments,  CefRefPtr<CefV8Value>& retval, CefString& exception);                    

    
private:
    CSWindow *mWindow;
    
    IMPLEMENT_REFCOUNTING(JSPluginUI);
};

#endif
