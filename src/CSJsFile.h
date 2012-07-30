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
