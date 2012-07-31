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

#include "CSJsSys.h"
#include "CSJsFile.h"
#include "CSUtil.h"

CSJsSys::CSJsSys(CSWindow *window) : CSJsModule(window)
{
    
}

void CSJsSys::Register(CefRefPtr<CefV8Value> windowObject)
{
    CefRefPtr<CefV8Value> obj = CefV8Value::CreateObject(NULL, NULL);
	
    RegFunc(obj, "log");
    RegFunc(obj, "file");
    RegFunc(obj, "os");
    
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
    else if (name == "os")
    {
        CefString osName = CSUtil::GetOS();
        retval = CefV8Value::CreateString(osName);
        return true;
    }

    return false;
}
