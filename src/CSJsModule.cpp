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
