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

#include "CSJsUi.h"
#include "CSJsMenu.h"

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
    RegFunc(obj, "setSize");
    RegFunc(obj, "move");
    RegFunc(obj, "screenSize");
    RegFunc(obj, "createWindow");
    RegFunc(obj, "menu");
    RegFunc(obj, "mainMenu");
    
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
    else if (name == "setSize")
    {
        if (arguments.size() == 2)
        {
            int width = arguments[0]->GetIntValue();
            int height = arguments[1]->GetIntValue();
            mWindow->SetSize(width, height);
            retval = CefV8Value::CreateNull();
            return true;            
        }
    }
    else if (name == "move")
    {
        if (arguments.size() == 2)
        {
            int x = arguments[0]->GetIntValue();
            int y = arguments[1]->GetIntValue();
            mWindow->SetPos(x, y);
            retval = CefV8Value::CreateNull();
            return true;            
        }
    }
    else if (name == "screenSize")
    {
        int width, height;
        mWindow->GetScreenSize(width, height);
        CefRefPtr<CefV8Value> obj = CefV8Value::CreateObject(NULL, NULL);
        obj->SetValue("width", CefV8Value::CreateInt(width), V8_PROPERTY_ATTRIBUTE_READONLY);
        obj->SetValue("height", CefV8Value::CreateInt(height), V8_PROPERTY_ATTRIBUTE_READONLY);
        retval = obj;
        return true;        
    }
    else if (name == "createWindow")
    {
        if (arguments.size() == 2)
        {
            int x = arguments[0]->GetIntValue();
            int y = arguments[1]->GetIntValue();
            mWindow->SetPos(x, y);
            retval = CefV8Value::CreateNull();
            return true;            
        }
    }
    else if (name == "menu")
    {
        if (arguments.size() == 1)
        {
            retval = CSJsMenu::CreateMenu(arguments[0]->GetStringValue());
            return true;
        }
    }
    else if (name == "mainMenu")
    {
        retval = CSJsMenu::GetMainMenu();
        return true;
    }
    
    return false;
}

