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
#include "CSJsMenuItem.h"

CSJsMenu::CSJsMenu(const CefString &name)
{
    mMenu = [[[NSMenu alloc] initWithTitle:[NSString stringWithUTF8String:name.ToString().c_str()]] autorelease];
    [mMenu retain];
}

CSJsMenu::CSJsMenu(NSMenu *menu)
{
    mMenu = menu;
    [menu retain];
}

CSJsMenu::~CSJsMenu()
{
    [mMenu release];
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
    NSMenu *nsMenu = [NSApp mainMenu];
    if (!nsMenu)
    {
        nsMenu = [[[NSMenu alloc] initWithTitle:@"MainMenu"] autorelease]; 
        [NSApp setMainMenu:nsMenu];
    }
    
    CSJsMenu *menu = new CSJsMenu(nsMenu);
    
    CefRefPtr<CefV8Value> obj = CefV8Value::CreateObject(menu, NULL);
    menu->BindFunction(obj);
    return obj;    
}

void CSJsMenu::AddMenuItem(const CefString &name, const CefString &hotkey, CefRefPtr<CefV8Value> callback, CefRefPtr<CefV8Context> context)
{
    NSString *nsName = [NSString stringWithCString:name.ToString().c_str() encoding:NSUTF8StringEncoding];
    NSString *nsHotkey = [NSString stringWithCString:hotkey.ToString().c_str() encoding:NSUTF8StringEncoding];
    CSJsMenuItem *menuItem = [[[CSJsMenuItem alloc] initWithTitle:nsName
                                                    keyEquivalent:nsHotkey
                                                         callback:callback
                                                          context:context] autorelease];

    [mMenu addItem:menuItem];
}

void CSJsMenu::AddSubMenu(const CefString &name, CefRefPtr<CefV8Value> menu)
{
    void *userData = menu->GetUserData().get();
    CSJsMenu *subMenu = static_cast<CSJsMenu *>(userData);

    NSString *title = [NSString stringWithCString:name.ToString().c_str() encoding:NSUTF8StringEncoding];
    NSMenuItem *item = [mMenu addItemWithTitle:title action:NULL keyEquivalent:@""];
	[mMenu setSubmenu:subMenu->mMenu forItem:item];
}

void CSJsMenu::Popup(int x, int y)
{
    NSWindow *window = [NSApp keyWindow];
    NSView *view = window.contentView;
    
    
    NSRect rect = [view frame];
    NSPoint menuOrigin = { x, rect.size.height - y };
    NSEvent *event = [NSEvent mouseEventWithType:NSLeftMouseDown
                                        location:menuOrigin
                                   modifierFlags:NSLeftMouseDownMask // 0x100
                                       timestamp:nil
                                    windowNumber:[window windowNumber]
                                         context:[window graphicsContext]
                                     eventNumber:0
                                      clickCount:1
                                        pressure:1];
    [NSMenu popUpContextMenu:mMenu withEvent:event forView:view];
}

bool CSJsMenu::Execute(const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception)
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
        Popup(arguments[0]->GetIntValue(), arguments[1]->GetIntValue());
        retval = CefV8Value::CreateNull();
        return true;        
    }
    
    return false;
}

void CSJsMenu::BindFunction(CefRefPtr<CefV8Value> obj)
{
    obj->SetValue("addItem", CefV8Value::CreateFunction("addItem", this), V8_PROPERTY_ATTRIBUTE_READONLY);    
    obj->SetValue("addSubMenu", CefV8Value::CreateFunction("addSubMenu", this), V8_PROPERTY_ATTRIBUTE_READONLY);    
    obj->SetValue("popup", CefV8Value::CreateFunction("popup", this), V8_PROPERTY_ATTRIBUTE_READONLY);    
}

