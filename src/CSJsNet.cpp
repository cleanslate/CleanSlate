/* 
 *
 * Copyright 2012 Yulius Tjahjadi <yultide@yahoo.com>
 *
 * This file is part of CleanSlate.
 * 
 * CleanSlate is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * CleanSlate is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License 
 * along with CleanSlate. If not, see http://www.gnu.org/licenses/.
 *
 */

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