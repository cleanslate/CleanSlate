//
//  CSWindow.h
//  CleanSlate
//
//  Created by Yulius Tjahjadi on 7/21/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef __CSWINDOW_H__
#define __CSWINDOW_H__

class CSBrowserClient;

class CSWindow
{
public:
    CSWindow();
    ~CSWindow();
    
    void *winHandle();
    void Show(bool show);
    void GetSize(int &width, int &height);
    void InvalidateRect(const CSRect &rect);
    void GetViewRect(CSRect &rect);
    void GetScreenPoint(int viewX, int viewY, int& screenX, int& screenY);
    void SetCursor(CefCursorHandle cursor);
    
private:
    void *mWindow;
    CSBrowserClient *mBrowserClient;
};

#endif
