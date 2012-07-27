//
//  CSWindow.mm
//  CleanSlate
//
//  Created by Yulius Tjahjadi on 7/21/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "CSWindow.h"

#include "CSBrowserClient.h"

#import "CSWindowImpl.h"
#import "CSView.h"

CSWindow::CSWindow()
{
    CSWindowImpl *window = [[CSWindowImpl alloc] init];

    [window setAlphaValue:1.0];
    [window setOpaque:NO];
    
    mWindow = window;
    
    // client
    CefWindowInfo windowInfo;
    CefBrowserSettings browserSettings;
    
    CSView *view = window.contentView;
    windowInfo.SetAsOffScreen(view);
    windowInfo.SetTransparentPainting(true);
    
    mBrowserClient = new CSBrowserClient(this);
    [view setBrowserClient:mBrowserClient];
    
    bool result = CefBrowser::CreateBrowser(windowInfo, mBrowserClient, "http://www.google.com/", browserSettings);
    if (!result)
        CSLogDebug("CefBrowser::CreateBrowser() failed");
    else
        CSLogDebug("Browser created");
}

CSWindow::~CSWindow()
{
    delete mBrowserClient;
    
    [(id)mWindow release];
}

void CSWindow::Show(bool show)
{
    [(id)mWindow makeKeyAndOrderFront:nil];
}

void CSWindow::GetSize(int &width, int &height)
{
    width = height = 0;
    NSRect rect = [(id)mWindow frame];
    width = rect.size.width;
    height = rect.size.height;
}

void CSWindow::UpdateRect(unsigned char *buffer, int width, int height, const CSRect &rect)
{
    NSWindow *window = (NSWindow *)mWindow;
    CSView *view = (CSView *)[window contentView];

    NSSize nsSize = { width, height };
    NSRect nsRect = NSMakeRect(rect.x, rect.y, rect.width, rect.height);
    [view updateRect:buffer size:nsSize rect:nsRect];
}

void CSWindow::InvalidateRect(const CSRect &rect)
{
    NSWindow *window = (NSWindow *)mWindow;
    NSView *view = [window contentView];
    
    NSRect nsRect = [(id)mWindow frame];
    float y = nsRect.size.height - rect.height - rect.y;
    
    [view setNeedsDisplayInRect:NSMakeRect(rect.x, y, rect.width, rect.height)];
}

void CSWindow::GetViewRect(CSRect &rect)
{
    NSWindow *window = (NSWindow *)mWindow;
    NSView *view = [window contentView];
    
    // The simulated screen and view rectangle are the same. This is necessary
    // for popup menus to be located and sized inside the view.
    const NSRect bounds = [view bounds];
    rect.x = rect.y = 0;
    rect.width = bounds.size.width;
    rect.height = bounds.size.height;
}

void CSWindow::GetScreenPoint(int viewX, int viewY, int& screenX, int& screenY)
{
    NSWindow *window = (NSWindow *)mWindow;
    NSView *view = [window contentView];

    // Convert the point from view coordinates to actual screen coordinates.
    NSRect bounds = [view bounds];
    NSPoint view_pt = {viewX, bounds.size.height - viewY};
    NSPoint window_pt = [view convertPoint:view_pt toView:nil];
    NSPoint screen_pt = [[view window] convertBaseToScreen:window_pt];
    screenX = screen_pt.x;
    screenY = screen_pt.y;
}

void CSWindow::SetCursor(CefCursorHandle cursor)
{
    [cursor set];
}

