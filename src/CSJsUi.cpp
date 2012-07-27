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

CSJsUi::CSJsUi(CSWindow *window) :
    mWindow(window)
{
    
}

CSJsUi::~CSJsUi()
{

}

void CSJsUi::Register(CefRefPtr<CefV8Value> windowObject)
{
	CefRefPtr<CefV8Value> uiObject = CefV8Value::CreateObject(NULL, NULL);
	
	// register functions
#define REGISTER_JS_FUNC(func) uiObject->SetValue(func, CefV8Value::CreateFunction(func, this), V8_PROPERTY_ATTRIBUTE_READONLY)
	REGISTER_JS_FUNC("startMove");
	REGISTER_JS_FUNC("stopMove");
	REGISTER_JS_FUNC("startResize");
	REGISTER_JS_FUNC("stopResize");
	REGISTER_JS_FUNC("show");
	REGISTER_JS_FUNC("close");
	REGISTER_JS_FUNC("setSizeHints");
#undef REGISTER_JS_FUNC
    
	// bind window.ui object
	windowObject->SetValue("ui", uiObject, V8_PROPERTY_ATTRIBUTE_READONLY);    
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

