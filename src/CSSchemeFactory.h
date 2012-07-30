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

#ifndef __CSSCHEMEFACTORY_H__
#define __CSSCHEMEFACTORY_H__

class CSSchemeFactory: public CefSchemeHandlerFactory
{
public:
    CSSchemeFactory();
    virtual ~CSSchemeFactory();
    
    static void Register();
    
    // CefSchemeHandlerFactory
    virtual CefRefPtr<CefSchemeHandler> Create(CefRefPtr<CefBrowser> browser, const CefString& scheme_name, CefRefPtr<CefRequest> request);
    
    IMPLEMENT_REFCOUNTING(UIBrowserSchemeFactory);
};



#endif
