//
//  CSJsSys.h
//  CleanSlate
//
//  Created by Yulius Tjahjadi on 7/27/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef __CSJSSYS_H__
#define __CSJSSYS_H__

#include "CSJsModule.h"

class CSWindow;

class CSJsSys: public CSJsModule
{
public:
    CSJsSys(CSWindow *window);
    
    void Register(CefRefPtr<CefV8Value> windowObject);
    
    virtual bool Execute(const CefString& name,  CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments,  CefRefPtr<CefV8Value>& retval, CefString& exception);
};

#endif
