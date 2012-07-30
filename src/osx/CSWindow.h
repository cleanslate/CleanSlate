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
