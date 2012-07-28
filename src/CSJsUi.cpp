//
//  CSJsUi.cpp
//  CleanSlate
//
//  Created by Yulius Tjahjadi on 7/27/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "CSPrecomp.h"

#include "CSJsUi.h"

#include "CSWindow.h"

CSJsUi::CSJsUi(CSWindow *window) : CSJsModule(window)
{
    
}

void CSJsUi::Register(CefRefPtr<CefV8Value> windowObject)
{
	CefRefPtr<CefV8Value> obj = CefV8Value::CreateObject(NULL, NULL);
	
    RegFunc(obj, "startMove");
    RegFunc(obj, "stopMove");
    RegFunc(obj, "startResize");
    RegFunc(obj, "stopResize");
    RegFunc(obj, "show");
    RegFunc(obj, "close");
    RegFunc(obj, "setSizeHints");
    
	// bind window.ui object
	windowObject->SetValue("ui", obj, V8_PROPERTY_ATTRIBUTE_READONLY);    
}

bool CSJsUi::Execute(const CefString& name,  CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments,  CefRefPtr<CefV8Value>& retval, CefString& exception)
{
    if (name == "startMove")
    {
        mWindow->StartMove();
		retval = CefV8Value::CreateNull();
		return true;
    }
    else if (name == "stopMove")
    {
        mWindow->StopMove();
		retval = CefV8Value::CreateNull();
		return true;        
    }
    else if (name == "startResize")
    {
        mWindow->StartResize();
		retval = CefV8Value::CreateNull();
		return true;            
    }
    else if (name == "stopResize")
    {
        mWindow->StopResize();
		retval = CefV8Value::CreateNull();
		return true;            
    }
    else if (name == "show")
    {
		if (arguments.size() == 1)
		{
			CefRefPtr<CefV8Value> showWindow = arguments[0];
			bool show = showWindow->GetBoolValue();
            mWindow->Show(show);
		}
		retval = CefV8Value::CreateNull();
		return true;            
    }
    else if (name == "close")
    {
        mWindow->Close();
		retval = CefV8Value::CreateNull();
		return true;            
    }
    
    return false;
}

