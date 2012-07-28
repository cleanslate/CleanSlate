//
//  CSJsModule.cpp
//  CleanSlate
//
//  Created by Yulius Tjahjadi on 7/27/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "CSPrecomp.h"
#include "CSJsModule.h"

CSJsModule::CSJsModule(CSWindow *window) :
    mWindow(window)
{
    
}

CSJsModule::~CSJsModule()
{
    
}

void CSJsModule::RegFunc(CefRefPtr<CefV8Value> obj, const CefString &name)
{
    obj->SetValue(name, CefV8Value::CreateFunction(name, this), V8_PROPERTY_ATTRIBUTE_READONLY);
}
