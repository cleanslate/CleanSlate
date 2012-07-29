//
//  CSJsNet.h
//  CleanSlate
//
//  Created by Yulius Tjahjadi on 7/28/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef __CSJSNET_H__
#define __CSJSNET_H__

#include "CSJsModule.h"

class CSWindow;

class CSJsNet : public CSJsModule
{
public:
    CSJsNet(CSWindow *window);    
    
    void Register(CefRefPtr<CefV8Value> windowObject);
    
    virtual bool Execute(const CefString& name,  CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments,  CefRefPtr<CefV8Value>& retval, CefString& exception);                    
    
};

#endif

