#ifndef __CSWINDOW_H__
#define __CSWINDOW_H__

class CSBrowserClient;
struct CSRect;

class CSWindow
{
public:
    CSWindow();
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

	void CreateBitmap(int width, int height);
};

#endif