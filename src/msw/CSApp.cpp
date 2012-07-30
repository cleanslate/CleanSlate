#include "CSPrecomp.h"

#include "CSApp.h"
#include "CSWindow.h"

#include "CSSchemeFactory.h"

static void WINAPI OnTimer(HWND hwnd, UINT msg, int id, DWORD t)
{
	event_loop(EVLOOP_ONCE);
}

CSApp::CSApp()
{

}

CSApp::~CSApp()
{

}

void CSApp::Init()
{
	WSADATA wsaData;
	DWORD err = WSAStartup(MAKEWORD(2,2), &wsaData);
	if (err != 0)
	{
		CSLogError("WSAStatup() failed. Error %d", err);
	}


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

	// Initialize event
	event_init();

	// Register the local scheme
	CSSchemeFactory::Register();
}

void CSApp::Run()
{
	CSWindow *window = new CSWindow();
	window->Show(true);

	// create timer
	SetTimer(NULL, 1, 100, (TIMERPROC)OnTimer);

    // Run the application message loop.
    CefRunMessageLoop();
}

void CSApp::Cleanup()
{
	WSACleanup();
}
