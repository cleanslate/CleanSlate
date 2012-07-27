//
//  CSSchemeFactory.cpp
//  CleanSlate
//
//  Created by Yulius Tjahjadi on 7/26/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "CSSchemeFactory.h"
#include "CSSchemeLocalHandler.h"

CSSchemeFactory::CSSchemeFactory()
{
    
}

CSSchemeFactory::~CSSchemeFactory()
{
    
}

void CSSchemeFactory::Register()
{
    CefRegisterCustomScheme(LOCAL_SCHEME, false, false, false);
    CefRegisterSchemeHandlerFactory(LOCAL_SCHEME, "", new CSSchemeFactory());
}

CefRefPtr<CefSchemeHandler> CSSchemeFactory::Create(CefRefPtr<CefBrowser> browser, const CefString& scheme_name, CefRefPtr<CefRequest> request)
{
    return new CSSchemeLocalHandler();
}
