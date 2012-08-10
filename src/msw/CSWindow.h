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
struct CSRect;

class CSWindow
{
public:
    CSWindow(const char *url);
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

	// windows specific
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
    HWND mWindow;
    CSBrowserClient *mBrowserClient;
	HDC mMemDC;
	HBITMAP mBitmap;
	SIZE mBitmapSize;
	unsigned char *mBitmapBits;

	// mouse move
	POINT mMouseStartPos;
	RECT mMouseStartRect;
	bool mMoving;
	bool mResizing;

	void OnPaint(WPARAM wParam, LPARAM lParam);
	void OnSize(WPARAM wParam, LPARAM lParam);
	void OnMouseLeftDown(WPARAM wParam, LPARAM lParam);
	void OnMouseLeftUp(WPARAM wParam, LPARAM lParam);
	void OnMouseRightDown(WPARAM wParam, LPARAM lParam);
	void OnMouseRightUp(WPARAM wParam, LPARAM lParam);
	void OnMouseMiddleDown(WPARAM wParam, LPARAM lParam);
	void OnMouseMiddleUp(WPARAM wParam, LPARAM lParam);
	void OnMouseMove(WPARAM wParam, LPARAM lParam);
	void OnMouseWheel(WPARAM wParam, LPARAM lParam);
	void OnKeyEvent(UINT msg, WPARAM wParam, LPARAM lParam);

	void CreateBitmap(int width, int height);
};

#endif