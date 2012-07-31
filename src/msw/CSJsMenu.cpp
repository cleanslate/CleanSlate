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

#include "CSJsMenu.h"


CSJsMenu::CallbackMap CSJsMenu::mCallback;

struct CallbackInfo
{
	CefRefPtr<CefV8Value> Value;
	CefRefPtr<CefV8Context> Context;
};

CSJsMenu::CSJsMenu(const CefString &name)
{
	mMenu = ::CreatePopupMenu();
}

CSJsMenu::~CSJsMenu()
{
	DestroyMenu(mMenu);
}
    
CefRefPtr<CefV8Value> CSJsMenu::CreateMenu(const CefString &name)
{
    CSJsMenu *menu = new CSJsMenu(name);

    CefRefPtr<CefV8Value> obj = CefV8Value::CreateObject(menu, NULL);
    menu->BindFunction(obj);    
    return obj;
}

CefRefPtr<CefV8Value> CSJsMenu::GetMainMenu()
{
	return NULL;
}
    
void CSJsMenu::AddMenuItem(const CefString &name, const CefString &hotkey, CefRefPtr<CefV8Value> callback, CefRefPtr<CefV8Context> context)
{
	DWORD menuId = GetMenuId();
	AppendMenu(mMenu, MF_STRING, menuId, name.ToWString().c_str());

	CallbackInfo contextInfo;
	contextInfo.Value = callback;
	contextInfo.Context = context;
	mCallback.insert(std::pair<DWORD, CallbackInfo>(menuId, contextInfo));
}

void CSJsMenu::AddSubMenu(const CefString &name, CefRefPtr<CefV8Value> menu)
{
    void *userData = menu->GetUserData().get();
    CSJsMenu *subMenu = static_cast<CSJsMenu *>(userData);

	AppendMenu(mMenu, MF_STRING | MF_POPUP, (UINT)subMenu->mMenu, name.ToWString().c_str());
}

void CSJsMenu::Popup(int x, int y)
{
	HWND hwnd = GetForegroundWindow();
	POINT pt = {x, y};
    MapWindowPoints(hwnd, HWND_DESKTOP, &pt, 1);

	BOOL result = TrackPopupMenu(mMenu, TPM_TOPALIGN | TPM_LEFTALIGN, pt.x, pt.y, 0, GetForegroundWindow(), NULL);
	DWORD err = GetLastError();
}

bool CSJsMenu::Execute(const CefString& name,  CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments,  CefRefPtr<CefV8Value>& retval, CefString& exception)
{
    if (name == "addItem")
    {
        if (arguments.size() == 3)
        {
            AddMenuItem(arguments[0]->GetStringValue(), arguments[1]->GetStringValue(), arguments[2], CefV8Context::GetCurrentContext());
            retval = CefV8Value::CreateNull();
            return true;
        }
    }
    else if (name == "addSubMenu")
    {
        if (arguments.size() == 2)
        {
            AddSubMenu(arguments[0]->GetStringValue(), arguments[1]);
            retval = CefV8Value::CreateNull();
            return true;
        }        
    }
	else if (name == "popup")
	{
        if (arguments.size() == 2)
        {
            Popup(arguments[0]->GetIntValue(), arguments[1]->GetIntValue());
            retval = CefV8Value::CreateNull();
            return true;
        } 
	}
    
    return false;
}

void CSJsMenu::OnMenuItemSelected(DWORD menuItem)
{
	CallbackMap::iterator iter = mCallback.find(menuItem);
	if (iter != mCallback.end())
	{
		CallbackInfo info = (*iter).second;

		CefV8ValueList args;
        CefRefPtr<CefV8Value> retval;
        CefRefPtr<CefV8Exception> exception;     

		info.Value->ExecuteFunctionWithContext(info.Context, NULL, args, retval, exception, false);
	}
}

void CSJsMenu::BindFunction(CefRefPtr<CefV8Value> obj)
{
    obj->SetValue("addItem", CefV8Value::CreateFunction("addItem", this), V8_PROPERTY_ATTRIBUTE_READONLY);    
    obj->SetValue("addSubMenu", CefV8Value::CreateFunction("addSubMenu", this), V8_PROPERTY_ATTRIBUTE_READONLY);    
    obj->SetValue("popup", CefV8Value::CreateFunction("popup", this), V8_PROPERTY_ATTRIBUTE_READONLY);    
}

DWORD CSJsMenu::GetMenuId()
{
	static DWORD MenuId = 9000;
	return MenuId++;
}