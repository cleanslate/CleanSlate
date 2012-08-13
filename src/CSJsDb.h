//
//  CSJsDb.h
//  CleanSlate
//
//  Created by Yulius Tjahjadi on 8/7/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef __CSJSDB_H__
#define __CSJSDB_H__

struct sqlite3;

class CSJsDb : public CefV8Handler
{
public:
    CSJsDb();
    ~CSJsDb();
    
    static CefRefPtr<CefV8Value> CreateDb();
    
    bool Exists(CefRefPtr<CefV8Value> dbName);
    bool Open(CefRefPtr<CefV8Value> dbName);
    bool OpenEncrypted(CefRefPtr<CefV8Value> dbName, CefRefPtr<CefV8Value> password);
    void Close();
    bool Delete(CefRefPtr<CefV8Value> dbName);
    CefRefPtr<CefV8Value> Sql(CefRefPtr<CefV8Value> sql);
    
    virtual bool Execute(const CefString& name,  CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments,  CefRefPtr<CefV8Value>& retval, CefString& exception);
    
private:
    struct sqlite3 *mDb;

    IMPLEMENT_REFCOUNTING(CSJsSocket);
};


#endif
