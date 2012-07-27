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
    void InvalidateRect(const CSRect &rect);
    void GetViewRect(CSRect &rect);
    void GetScreenPoint(int viewX, int viewY, int& screenX, int& screenY);
    void SetCursor(CefCursorHandle cursor);

private:
    void *mWindow;
    CSBrowserClient *mBrowserClient;
};

#endif