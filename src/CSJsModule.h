//
//  CSJsModule.h
//  CleanSlate
//
//  Created by Yulius Tjahjadi on 7/27/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef __CSJSMODULE_H__
#define __CSJSMODULE_H__

class CSWindow;

class CSJsModule : public CefV8Handler
{
public:
    CSJsModule(CSWindow *window);
    virtual ~CSJsModule();
        
    void RegFunc(CefRefPtr<CefV8Value> obj, const CefString &name);
    
protected:
    CSWindow *mWindow;
    
    IMPLEMENT_REFCOUNTING(CSJsModule);
};

#endif
