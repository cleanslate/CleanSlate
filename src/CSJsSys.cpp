//
//  CSJsSys.cpp
//  CleanSlate
//
//  Created by Yulius Tjahjadi on 7/27/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "CSPrecomp.h"

#include "CSJsSys.h"
#include "CSJsFile.h"

CSJsSys::CSJsSys(CSWindow *window) : CSJsModule(window)
{
    
}

void CSJsSys::Register(CefRefPtr<CefV8Value> windowObject)
{
    CefRefPtr<CefV8Value> obj = CefV8Value::CreateObject(NULL, NULL);
	
    RegFunc(obj, "log");
    RegFunc(obj, "file");
    
	// bind window.ui object
	windowObject->SetValue("sys", obj, V8_PROPERTY_ATTRIBUTE_READONLY);
}

bool CSJsSys::Execute(const CefString& name,  CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments,  CefRefPtr<CefV8Value>& retval, CefString& exception)
{
    if (name == "log")
	{
		if (arguments.size() == 1)
		{
			arguments[0]->GetStringValue().ToWString();
            CSLogInfo("JSLOG: %s", arguments[0]->GetStringValue().ToString().c_str());
		}
		retval = CefV8Value::CreateNull();
		return true;
    }
    else if (name == "file")
    {
		retval = CSJsFile::CreateFile();
		return true;        
    }

    return false;
}
