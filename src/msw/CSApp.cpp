#include "CSPrecomp.h"

#include "CSApp.h"
#include "CSWindow.h"

CSApp::CSApp()
{

}

CSApp::~CSApp()
{

}

void CSApp::Init()
{
	WNDCLASS wc;
    HINSTANCE hInstance = GetModuleHandle(NULL);

    // Register the window class.
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = CSWindow::WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = L"CSWindowClass";
    RegisterClass(&wc);

	CefSettings settings;
    CefRefPtr<CefApp> app;
    
    // Initialize CEF.
    CefInitialize(settings, app);
}

void CSApp::Run()
{
	CSWindow *window = new CSWindow();
	window->Show(true);

    // Run the application message loop.
    CefRunMessageLoop();
}

void CSApp::Cleanup()
{
	
}
