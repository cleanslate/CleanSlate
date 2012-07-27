#include "CSPrecomp.h"
#include "CSWindow.h"
#include "CSBrowserClient.h"

CSWindow::CSWindow() :
	mWindow(NULL),
	mResizing(false),
	mMoving(false),
	mBitmap(NULL),
	mMemDC(NULL)
{
	HINSTANCE hInstance = GetModuleHandle(NULL);

	int width = 640;
	int height = 480;

	HWND window = CreateWindowEx(WS_EX_LAYERED, L"CSWindowClass", L"",
        WS_POPUP, CW_USEDEFAULT, CW_USEDEFAULT, width, height, NULL, NULL,
        hInstance, NULL);

	DWORD err = GetLastError();

	SetWindowLongPtr(window, GWLP_USERDATA, (LONG_PTR)this);

	mBrowserClient = new CSBrowserClient(this);

	// create browser
    CefWindowInfo windowInfo;
    CefBrowserSettings settings;
    windowInfo.SetAsOffScreen(window);
    windowInfo.SetTransparentPainting(TRUE);
    CefBrowser::CreateBrowser(windowInfo, mBrowserClient, "local://index.html", settings);

	// create bitmap
	CreateBitmap(width, height);

	mWindow = window;
}

CSWindow::~CSWindow()
{
	SelectObject(mMemDC, NULL);
	DeleteObject(mBitmap);
	DeleteDC(mMemDC);

	//delete mBrowserClient;
	DestroyWindow(mWindow);
}

void CSWindow::Show(bool show)
{
	ShowWindow(mWindow, show ? SW_SHOW : SW_HIDE);
}

void CSWindow::GetSize(int &width, int &height)
{
	RECT rect;
	GetClientRect(mWindow, &rect);

	width = rect.right - rect.left;
	height = rect.bottom - rect.top;
}

void CSWindow::UpdateRect(unsigned char *buffer, int width, int height, const CSRect &rect)
{
	// update bitmap if size changes
	if (mBitmapSize.cx != width || mBitmapSize.cy != height)
	{
		CreateBitmap(width, height);
	}

	// copy rects
    for (int y = rect.y; y < rect.y + rect.height; y++)
    {
        int offset = (y*width + rect.x) * 4;
        unsigned char *dst = &mBitmapBits[offset];
        const unsigned char *src = &buffer[offset];
        for (int x = rect.x; x < rect.x + rect.width; x++)
        {
            dst[0] = src[0]; // R
            dst[1] = src[1]; // G
            dst[2] = src[2]; // B
            dst[3] = src[3]; // A

			dst += 4;
            src += 4;
        }
    }

	// resize window if needed
	RECT r;
	GetWindowRect(mWindow, &r);
	if (width != r.right - r.left || height != r.bottom - r.top)
	{
		MoveWindow(mWindow, r.left, r.top, width, height, TRUE);
	}
}

void CSWindow::InvalidateRect(const CSRect &rect)
{
	RECT r;
	r.left = rect.x;
	r.top = rect.y;
	r.right = rect.x + rect.width;
	r.bottom = rect.y + rect.height;
	::InvalidateRect(mWindow, &r, TRUE);
}

void CSWindow::GetViewRect(CSRect &rect)
{
	RECT r;
	GetClientRect(mWindow, &r);

	rect.x = r.left;
	rect.y = r.top;
	rect.width = r.right - r.left;
	rect.height = r.bottom - r.top;
}

void CSWindow::GetScreenPoint(int viewX, int viewY, int& screenX, int& screenY)
{
	POINT screen_pt = {viewX, viewY};
    MapWindowPoints(mWindow, HWND_DESKTOP, &screen_pt, 1);
    screenX = screen_pt.x;
    screenY = screen_pt.y;
}

void CSWindow::SetCursor(CefCursorHandle cursor)
{
	// Change the plugin window's cursor.
    SetClassLong(mWindow, GCL_HCURSOR, (LONG)cursor);
    ::SetCursor(cursor);
}

void CSWindow::Close()
{
	SendMessage(mWindow, WM_CLOSE, 0, 0);
}

void CSWindow::Destroy()
{
	DestroyWindow(mWindow);
	delete this;
}

void CSWindow::StartMove()
{
	SetCapture(mWindow);

    GetCursorPos(&mMouseStartPos);
	GetWindowRect(mWindow, &mMouseStartRect);
	mMoving = true;
}

void CSWindow::StopMove()
{
	ReleaseCapture();
	mMoving = false;
}

void CSWindow::StartResize()
{
	SetCapture(mWindow);

    GetCursorPos(&mMouseStartPos);
	GetWindowRect(mWindow, &mMouseStartRect);
	mResizing = true;
}

void CSWindow::StopResize()
{
	ReleaseCapture();
	mResizing = false;
}

void CSWindow::OnPaint(WPARAM wParam, LPARAM lParam)
{
	if (mBrowserClient)
    {
        int width, height;
        mBrowserClient->GetBrowserSize(width, height);
        if (width > 0 && height > 0)
        {
			static POINT ptZero = { 0 };
			SIZE szSize = { width, height };

			BLENDFUNCTION blend = { 0 };
			blend.BlendOp = AC_SRC_OVER;
			blend.SourceConstantAlpha = 255;
			blend.AlphaFormat = AC_SRC_ALPHA;
		
			HDC desktopDC = GetDC(HWND_DESKTOP);

			UpdateLayeredWindow((HWND)mWindow, desktopDC, NULL, &szSize,
				mMemDC, &ptZero, RGB(0, 0, 0), &blend, ULW_ALPHA);

			ReleaseDC(HWND_DESKTOP, desktopDC);
        }
    }
}

void CSWindow::OnSize(WPARAM wParam, LPARAM lParam)
{
	//int width  = LOWORD(lParam);
    //int height = HIWORD(lParam);
    //if (width > 0 && height > 0 && mBrowserClient && mBrowserClient->GetBrowser().get())
	//	mBrowserClient->GetBrowser()->SetSize(PET_VIEW, width, height);
}

void CSWindow::OnMouseLeftDown(WPARAM wParam, LPARAM lParam)
{
	if (mBrowserClient && mBrowserClient->GetBrowser().get())
		mBrowserClient->GetBrowser()->SendMouseClickEvent(LOWORD(lParam), HIWORD(lParam), MBT_LEFT, false, 1);
}

void CSWindow::OnMouseLeftUp(WPARAM wParam, LPARAM lParam)
{
	mResizing = mMoving = FALSE;

	if (mBrowserClient && mBrowserClient->GetBrowser().get())
		mBrowserClient->GetBrowser()->SendMouseClickEvent(LOWORD(lParam), HIWORD(lParam), MBT_LEFT, true, 1);
}

void CSWindow::OnMouseRightDown(WPARAM wParam, LPARAM lParam)
{
	if (mBrowserClient && mBrowserClient->GetBrowser().get())
		mBrowserClient->GetBrowser()->SendMouseClickEvent(LOWORD(lParam), HIWORD(lParam), MBT_RIGHT, false, 1);
}

void CSWindow::OnMouseRightUp(WPARAM wParam, LPARAM lParam)
{
	if (mBrowserClient && mBrowserClient->GetBrowser().get())
		mBrowserClient->GetBrowser()->SendMouseClickEvent(LOWORD(lParam), HIWORD(lParam), MBT_RIGHT, true, 1);
}

void CSWindow::OnMouseMiddleDown(WPARAM wParam, LPARAM lParam)
{
	if (mBrowserClient && mBrowserClient->GetBrowser().get())
		mBrowserClient->GetBrowser()->SendMouseClickEvent(LOWORD(lParam), HIWORD(lParam), MBT_MIDDLE, false, 1);
}

void CSWindow::OnMouseMiddleUp(WPARAM wParam, LPARAM lParam)
{
	if (mBrowserClient && mBrowserClient->GetBrowser().get())
		mBrowserClient->GetBrowser()->SendMouseClickEvent(LOWORD(lParam), HIWORD(lParam), MBT_MIDDLE, true, 1);
}

void CSWindow::OnMouseMove(WPARAM wParam, LPARAM lParam)
{
	if (mMoving)
	{
		POINT pt;
		GetCursorPos(&pt);
		
		POINT diff = { pt.x - mMouseStartPos.x, pt.y - mMouseStartPos.y };
		MoveWindow(mWindow, mMouseStartRect.left + diff.x, mMouseStartRect.top + diff.y,
			mMouseStartRect.right - mMouseStartRect.left, mMouseStartRect.bottom - mMouseStartRect.top, FALSE);
		
		return;
	}

	if (mResizing)
	{
		POINT pt;
		GetCursorPos(&pt);

		POINT diff = { pt.x - mMouseStartPos.x, pt.y - mMouseStartPos.y };
		SIZE size = { mMouseStartRect.right - mMouseStartRect.left + diff.x, mMouseStartRect.bottom - mMouseStartRect.top + diff.y };

		CSLogDebug("Resize %dx%d", size.cx, size.cy);
		if (mBrowserClient)
            mBrowserClient->SetBrowserSize(size.cx, size.cy);

		return;
	}

	if (mBrowserClient && mBrowserClient->GetBrowser().get())
		mBrowserClient->GetBrowser()->SendMouseMoveEvent(LOWORD(lParam), HIWORD(lParam), false);
}

void CSWindow::OnMouseWheel(WPARAM wParam, LPARAM lParam)
{
	if (mBrowserClient && mBrowserClient->GetBrowser().get())
		mBrowserClient->GetBrowser()->SendMouseWheelEvent(LOWORD(lParam), HIWORD(lParam), GET_WHEEL_DELTA_WPARAM(wParam));
}


void CSWindow::CreateBitmap(int width, int height)
{
	BITMAPINFO bmi = {0};
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = width;
	bmi.bmiHeader.biHeight = -height; // top-down
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biCompression = BI_RGB;

	if (!mMemDC)
		mMemDC = CreateCompatibleDC(NULL);

	if (mBitmap)
		DeleteObject(mBitmap);

	mBitmap = CreateDIBSection(mMemDC, &bmi, DIB_RGB_COLORS, (void **)&mBitmapBits, NULL, NULL);
	
	SelectObject(mMemDC, mBitmap);
	mBitmapSize.cx = width;
	mBitmapSize.cy = height;

}

LRESULT CSWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	CSWindow *win = (CSWindow *)GetWindowLongPtr(hWnd, GWLP_USERDATA);

	if (!win)
		return DefWindowProc(hWnd, message, wParam, lParam);

	switch (message)
	{
	case WM_PAINT:
		win->OnPaint(wParam, lParam);
		break;

	case WM_SIZE:
		win->OnSize(wParam, lParam);
		break;

	case WM_LBUTTONDOWN:
		win->OnMouseLeftDown(wParam, lParam);
		break;

	case WM_LBUTTONUP:
		win->OnMouseLeftUp(wParam, lParam);
		break;

	case WM_RBUTTONDOWN:
		win->OnMouseRightDown(wParam, lParam);
		break;

	case WM_RBUTTONUP:
		win->OnMouseRightUp(wParam, lParam);
		break;

	case WM_MBUTTONDOWN:
		win->OnMouseMiddleDown(wParam, lParam);
		break;

	case WM_MBUTTONUP:
		win->OnMouseMiddleUp(wParam, lParam);
		break;

	case WM_MOUSEMOVE:
		win->OnMouseMove(wParam, lParam);
		break;

	case WM_MOUSEWHEEL:
		win->OnMouseWheel(wParam, lParam);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_CLOSE:
		delete win;
		break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}
