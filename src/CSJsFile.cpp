//
//  CSJsFile.cpp
//  CleanSlate
//
//  Created by Yulius Tjahjadi on 7/30/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "CSPrecomp.h"

#include "CSJsFile.h"

CSJsFile::CSJsFile() :
    mFile(NULL)
{
    
}

CSJsFile::~CSJsFile()
{
    Close();
}

CefRefPtr<CefV8Value> CSJsFile::CreateFile()
{
    CSJsFile *file = new CSJsFile();
    
    CefRefPtr<CefV8Value> obj = CefV8Value::CreateObject(file, NULL);
    
    // bind functions
    obj->SetValue("open", CefV8Value::CreateFunction("open", file), V8_PROPERTY_ATTRIBUTE_READONLY);
    obj->SetValue("close", CefV8Value::CreateFunction("close", file), V8_PROPERTY_ATTRIBUTE_READONLY);
    obj->SetValue("size", CefV8Value::CreateFunction("size", file), V8_PROPERTY_ATTRIBUTE_READONLY);
    obj->SetValue("seek", CefV8Value::CreateFunction("seek", file), V8_PROPERTY_ATTRIBUTE_READONLY);
    obj->SetValue("seekEnd", CefV8Value::CreateFunction("seekEnd", file), V8_PROPERTY_ATTRIBUTE_READONLY);
    obj->SetValue("read", CefV8Value::CreateFunction("read", file), V8_PROPERTY_ATTRIBUTE_READONLY);
    obj->SetValue("write", CefV8Value::CreateFunction("write", file), V8_PROPERTY_ATTRIBUTE_READONLY);
    
    return obj;
}


bool CSJsFile::Open(const CefString &path, const char *mode)
{
    mFile = fopen(path.ToString().c_str(), mode);
    return mFile != NULL;
}

void CSJsFile::Close()
{
    if (mFile)
    {
        fclose(mFile);
        mFile = NULL;
    }
}

off_type CSJsFile::Size()
{
    off_type pos = Pos();
    SeekEnd();
    off_type size = Pos();
    Seek(pos);
    
    return size;
}

off_type CSJsFile::Pos()
{
    return ftell64(mFile);
}

bool CSJsFile::Seek(off_type pos)
{
    return fseek64(mFile, pos, SEEK_SET) == 0;
}

bool CSJsFile::SeekEnd()
{
    return fseek64(mFile, 0, SEEK_END) == 0;
}

int CSJsFile::Read(void *data, int size)
{
    return fread(data, 1, size, mFile);
}

int CSJsFile::Write(void *data, int size)
{
    return fwrite(data, 1, size, mFile);
}

bool CSJsFile::Execute(const CefString& name,  CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments,  CefRefPtr<CefV8Value>& retval, CefString& exception)
{
    if (name == "open")
    {
        if (arguments.size() == 2)
        {
            CefString path = arguments[0]->GetStringValue();
            CefString mode = arguments[1]->GetStringValue();
            
            bool result = Open(path.ToString().c_str(), mode.ToString().c_str());
            
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
    else if (name == "size")
    {
        off_type size = Size();
        retval = CefV8Value::CreateDouble((double)size);
        return true;
    }
    else if (name == "pos")
    {
        off_type pos = Pos();
        retval = CefV8Value::CreateDouble((double)pos);
        return true;
    }
    else if (name == "seek")
    {
        if (arguments.size() == 1)
        {
            off_type pos = (off_type)arguments[0]->GetDoubleValue();
            retval = CefV8Value::CreateBool(Seek(pos));
            return true;
        }
    }
    else if (name == "seekEnd")
    {
        retval = CefV8Value::CreateBool(SeekEnd());
        return true;
    }
    else if (name == "read")
    {
        if (arguments.size() == 1)
        {
            std::string str;
            str.resize(arguments[0]->GetIntValue());
            int value = Read(&str[0], str.size());
            if (value != str.size())
                str.resize(value);
            
            retval = CefV8Value::CreateString(str);
            return true;
        }
    }
    else if (name == "write")
    {
        if (arguments.size() == 1)
        {
            std::string str = arguments[0]->GetStringValue().ToString();
            int value = Write(&str[0], str.size());
            if (value != str.size())
                str.resize(value);
            
            retval = CefV8Value::CreateString(str);
            return true;
        }        
    }
    
    return false;
}

