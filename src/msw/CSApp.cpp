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

#include "CSPrecomp.h"

#include "CSApp.h"
#include "CSWindow.h"
#include "CSConfig.h"
#include "CSUtil.h"

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
	//CSWindow *window = new CSWindow("local://file/chat/login.html");
	//window->Show(true);
	std::string configPath = CSUtil::GetLocalDir();
	configPath.append("/config.json");

	CSConfig config;
	config.LoadConfig(configPath.c_str());

	// create timer
	SetTimer(NULL, 1, 100, (TIMERPROC)OnTimer);

    // Run the application message loop.
    CefRunMessageLoop();
}

void CSApp::Cleanup()
{
	WSACleanup();
}
