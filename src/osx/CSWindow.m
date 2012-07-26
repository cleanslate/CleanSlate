//
//  CSWindow.mm
//  CleanSlate
//
//  Created by Yulius Tjahjadi on 7/21/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "CSWindow.h"

#import "CSWindowImpl.h"

CSWindow::CSWindow()
{
    CSWindowImpl *window = [[CSWindowImpl alloc] init];

    [window setAlphaValue:1.0];
    [window setOpaque:NO];
    
    mWindow = window;
}

CSWindow::~CSWindow()
{
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
