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

#include "CSJsApp.h"
#include "CSWindow.h"
#include "CSJsDb.h"

CSJsApp::CSJsApp(CSWindow *window) : CSJsModule(window)
{
    mState = CefV8Value::CreateObject(NULL, NULL);
}	

void CSJsApp::Register(CefRefPtr<CefV8Value> windowObject)
{
    CefRefPtr<CefV8Value> obj = CefV8Value::CreateObject(NULL, NULL);
    
    RegFunc(obj, "db");
    
    // temporary state object to keep the state of the app
    obj->SetValue("state", mState, V8_PROPERTY_ATTRIBUTE_NONE);
	
	// bind window.ui object
	windowObject->SetValue("app", obj, V8_PROPERTY_ATTRIBUTE_READONLY);    
}

bool CSJsApp::Execute(const CefString& name,  CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments,  CefRefPtr<CefV8Value>& retval, CefString& exception)
{
    if (name == "db")
    {
        retval = CSJsDb::CreateDb();
        return true;
    }
    
    return false;
}
