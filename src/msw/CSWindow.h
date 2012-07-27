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
    
private:
    void *mWindow;
    CSBrowserClient *mBrowserClient;
};

#endif