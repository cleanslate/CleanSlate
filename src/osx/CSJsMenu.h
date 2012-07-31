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

#ifndef __CSJSMENU_H__
#define __CSJSMENU_H__

class CSJsMenu : public CefV8Handler
{
public:
    CSJsMenu(const CefString &name);
    CSJsMenu(NSMenu *menu);
    virtual ~CSJsMenu();
    
    static CefRefPtr<CefV8Value> CreateMenu(const CefString &name);
    static CefRefPtr<CefV8Value> GetMainMenu();
    
    void AddMenuItem(const CefString &name, const CefString &hotkey, CefRefPtr<CefV8Value> callback, CefRefPtr<CefV8Context> context);
    void AddSubMenu(const CefString &name, CefRefPtr<CefV8Value> menu);
    void Popup(int x, int y);
    
    virtual bool Execute(const CefString& name,  CefRefPtr<CefV8Value> object, 
                         const CefV8ValueList& arguments,  CefRefPtr<CefV8Value>& retval, CefString& exception);    
    
private:
    NSMenu *mMenu;
    
    void BindFunction(CefRefPtr<CefV8Value> obj);
    
    IMPLEMENT_REFCOUNTING(CSJsFile);
};

#endif
