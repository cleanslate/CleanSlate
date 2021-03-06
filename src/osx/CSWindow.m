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

#include "CSWindow.h"

#include "CSBrowserClient.h"

#import "CSWindowImpl.h"
#import "CSView.h"

CSWindow::CSWindow(const char *url)
{
    CSWindowImpl *window = [[[CSWindowImpl alloc] init] autorelease];
    [window retain];
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
    
    bool result = CefBrowser::CreateBrowser(windowInfo, mBrowserClient, url, browserSettings);
    if (!result)
        CSLogDebug("CefBrowser::CreateBrowser() failed");
    else
        CSLogDebug("Browser created");
}

CSWindow::~CSWindow()
{
    // we don't delete mWindow because calling close will automatically delete it
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

void CSWindow::Close()
{
    // tell the browser to close first
    mBrowserClient->GetBrowser()->CloseBrowser();
}

void CSWindow::Destroy()
{
    // called when browser is destroyed
    NSWindow *window = (NSWindow *)mWindow;
    [window close];

    // check to see if we should terminate the app
    NSApplication *app = [NSApplication sharedApplication];
    NSArray *windows = [app windows];
    if ([windows count] == 0)
        [app terminate:nil];

    // delete ourself
    delete this;
}

void CSWindow::StartMove()
{
    NSWindow *window = (NSWindow *)mWindow;
    CSView *view = (CSView *)[window contentView];
    
    [view startMove];
}

void CSWindow::StopMove()
{
    NSWindow *window = (NSWindow *)mWindow;
    CSView *view = (CSView *)[window contentView];
    
    [view stopMove];
}

void CSWindow::StartResize()
{
    NSWindow *window = (NSWindow *)mWindow;
    CSView *view = (CSView *)[window contentView];
    
    [view startResize];    
}

void CSWindow::StopResize()
{
    NSWindow *window = (NSWindow *)mWindow;
    CSView *view = (CSView *)[window contentView];
    
    [view stopResize];    
}

void CSWindow::SetSize(int width, int height)
{
    NSWindow *window = (NSWindow *)mWindow;
    CSView *view = (CSView *)[window contentView];

    [view setSize:NSMakeSize(width, height)];
}

void CSWindow::SetPos(int x, int y)
{
    NSWindow *window = (NSWindow *)mWindow;
    NSRect windowFrame = [window frame];
    NSRect frame = [[NSScreen mainScreen] visibleFrame];
    
    //NSPoint pt = NSMakePoint(x, frame.size.height - y - windowFrame.size.height);
    NSPoint pt = NSMakePoint(x, frame.size.height - y - windowFrame.size.height);

    [window setFrameOrigin:pt];
}

void CSWindow::GetScreenSize(int &width, int &height)
{
    NSScreen *screen = [NSScreen mainScreen];
    NSRect rect = [screen visibleFrame];
    width = rect.size.width;
    height = rect.size.height;
}
