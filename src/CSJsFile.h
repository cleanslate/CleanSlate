//
//  CSJsFile.h
//  CleanSlate
//
//  Created by Yulius Tjahjadi on 7/30/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef __CSJSFILE_H__
#define __CSJSFILE_H__

class CSJsFile : public CefV8Handler
{
public:
    CSJsFile();
    virtual ~CSJsFile();
    
    static CefRefPtr<CefV8Value> CreateFile();
    
    bool Open(const CefString &path, const char *mode);
    void Close();
    off_type Size();
    off_type Pos();
    bool Seek(off_type pos);
    bool SeekEnd();
    int Read(void *data, int size);
    int Write(void *data, int size);
    
    virtual bool Execute(const CefString& name,  CefRefPtr<CefV8Value> object, 
                         const CefV8ValueList& arguments,  CefRefPtr<CefV8Value>& retval, CefString& exception);    
    
private:
    FILE *mFile;
    
    IMPLEMENT_REFCOUNTING(CSJsFile);
};

#endif
