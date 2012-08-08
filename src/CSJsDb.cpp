//
//  CSJsDb.cpp
//  CleanSlate
//
//  Created by Yulius Tjahjadi on 8/7/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "CSPrecomp.h"

#include "CSJsDb.h"

#include <sqlite3.h>

CSJsDb::CSJsDb() :
    mDb(NULL)
{
}

CSJsDb::~CSJsDb()
{
    Close();
}

CefRefPtr<CefV8Value> CSJsDb::CreateDb()
{
    CSJsDb *db = new CSJsDb();
    CefRefPtr<CefV8Value> obj = CefV8Value::CreateObject(db, NULL);
    obj->SetValue("open", CefV8Value::CreateFunction("open", db), V8_PROPERTY_ATTRIBUTE_READONLY);
    obj->SetValue("close", CefV8Value::CreateFunction("close", db), V8_PROPERTY_ATTRIBUTE_READONLY);
    obj->SetValue("sql", CefV8Value::CreateFunction("sql", db), V8_PROPERTY_ATTRIBUTE_READONLY);
    
    return obj;
}


bool CSJsDb::Open(CefRefPtr<CefV8Value> dbname)
{
    Close();
    
    int retval = sqlite3_open_v2(dbname->GetStringValue().ToString().c_str(), &mDb, SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE, NULL);
    if (retval != SQLITE_OK)
    {
        CSLogError("Can't open database: %s\n", sqlite3_errmsg(mDb));
        return false;
    }
    return true;
}

void CSJsDb::Close()
{
    if (mDb)
        sqlite3_close(mDb);
}

CefRefPtr<CefV8Value> CSJsDb::Sql(CefRefPtr<CefV8Value> sqlStr)
{
    if (!mDb)
        return CefV8Value::CreateNull();
    
    std::string sql = sqlStr->GetStringValue().ToString();
    sqlite3_stmt *statement;
    
    int retval = sqlite3_prepare(mDb, sql.c_str(), -1, &statement, NULL);
    if (retval != SQLITE_OK)
    {
        CSLogError("Sql prepare failed: %s", sqlite3_errmsg(mDb));
        return false;
    }
    
    CefRefPtr<CefV8Value> result = CefV8Value::CreateArray();
    int rowIndex = 0;
    while (sqlite3_step(statement) == SQLITE_ROW)
    {
        CefRefPtr<CefV8Value> row = CefV8Value::CreateArray();
        int count = sqlite3_column_count(statement);
        for (int i = 0; i < count; i++)
        {
            int type = sqlite3_column_type(statement, i);
            CefRefPtr<CefV8Value> colValue;
            switch (type)
            {
                case SQLITE_INTEGER:
                    colValue = CefV8Value::CreateInt(sqlite3_column_int(statement, i));
                    break;
                case SQLITE_FLOAT:
                    colValue = CefV8Value::CreateDouble(sqlite3_column_double(statement, i));
                    break;
                case SQLITE_TEXT:
                    colValue = CefV8Value::CreateString((const char *)sqlite3_column_text(statement, i));
                    break;
                case SQLITE_NULL:
                default:
                    colValue = CefV8Value::CreateNull();
                    break;
            }
            row->SetValue(i, colValue);
        }
        
        result->SetValue(rowIndex, row);
        rowIndex++;
    }
    
    retval = sqlite3_finalize(statement);
    
    return result;
}

bool CSJsDb::Execute(const CefString& name,  CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments,  CefRefPtr<CefV8Value>& retval, CefString& exception)
{
    if (name == "open")
    {
        if (arguments.size() == 1)
        {
            bool result = Open(arguments[0]);
            retval = CefV8Value::CreateBool(result);
            return true;
        }
    }
    else if (name == "close")
    {
        Close();
        retval = CefV8Value::CreateNull();
        return true;
    }
    else if (name == "sql")
    {
        if (arguments.size() == 1)
        {
            retval = Sql(arguments[0]);
            return true;
        }
    }
    
    return false;
}

