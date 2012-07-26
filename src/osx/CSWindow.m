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

void *CSWindow::winHandle()
{
    return mWindow;
}

void CSWindow::GetSize(int &width, int &height)
{
    width = height = 0;
    NSRect rect = [(id)mWindow frame];
    width = rect.size.width;
    height = rect.size.height;
}

void CSWindow::InvalidateRect(const CSRect &rect)
{
    NSWindow *window = (NSWindow *)mWindow;
    NSView *view = [window contentView];
    
    NSRect nsRect;
    nsRect.origin.x = rect.x;
    nsRect.origin.y = rect.y;
    nsRect.size.width = rect.width;
    nsRect.size.height = rect.height;
    [view setNeedsDisplayInRect:nsRect];
}
