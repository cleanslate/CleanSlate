#include "CSPrecomp.h"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	CefSettings settings;
    CefRefPtr<CefApp> app;
    
    // Initialize CEF.
    CefInitialize(settings, app);
    
    // Run the application message loop.
    CefRunMessageLoop();

	return 0;
}