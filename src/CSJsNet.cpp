//
//  CSJsNet.cpp
//  CleanSlate
//
//  Created by Yulius Tjahjadi on 7/28/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "CSPrecomp.h"

#include "CSJsNet.h"
#include "CSJsSocket.h"

CSJsNet::CSJsNet(CSWindow *window) : CSJsModule(window)
{
    
}

void CSJsNet::Register(CefRefPtr<CefV8Value> windowObject)
{
    CefRefPtr<CefV8Value> obj = CefV8Value::CreateObject(NULL, NULL);
	
    RegFunc(obj, "socket");
    
	// bind window.ui object
	windowObject->SetValue("net", obj, V8_PROPERTY_ATTRIBUTE_READONLY);    
    
}

bool CSJsNet::Execute(const CefString& name,  CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments,  CefRefPtr<CefV8Value>& retval, CefString& exception)
{
    if (name == "socket")
	{
        if (arguments.size() == 2)
		{
            CefString hostname = arguments[0]->GetStringValue();
            int port = arguments[1]->GetIntValue();
            retval = CSJsSocket::CreateSocket(hostname, port);
		}
        else
        {
            retval = CefV8Value::CreateNull();
        }
		return true;
    }
    
    return false;
}