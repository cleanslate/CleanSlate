//
//  CSSchemeFactory.h
//  CleanSlate
//
//  Created by Yulius Tjahjadi on 7/26/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

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
