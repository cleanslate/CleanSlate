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
    CSWindow(int x, int y, int width, int height);
    ~CSWindow();
    
    void Show(bool show);
    void GetSize(int &width, int &height);
    void UpdateRect(unsigned char *buffer, int width, int height, const CSRect &rect);
    void InvalidateRect(const CSRect &rect);
    void GetViewRect(CSRect &rect);
    void GetScreenPoint(int viewX, int viewY, int& screenX, int& screenY);
    void SetCursor(CefCursorHandle cursor);
    void Close();
    void Destroy();
    
    // javascript functions
    void StartMove();
    void StopMove();
    void StartResize();
    void StopResize();
    void SetSize(int width, int height);
    void SetPos(int x, int y);
    void GetScreenSize(int &width, int &height);
    
private:
    void *mWindow;
    CSBrowserClient *mBrowserClient;
};

#endif
