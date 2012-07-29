//
//  AppDelegate.m
//  CleanSlate
//
//  Created by Yulius Tjahjadi on 7/20/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//
#import "AppDelegate.h"

#include "CSWindow.h"
#include "CSSchemeFactory.h"

@implementation AppDelegate

-(id) init
{
    if (self = [super init])
    {

    }
    return self;
}

-(void) dealloc
{
    //[window release];
    [super dealloc];
}

-(void) applicationWillFinishLaunching:(NSNotification *)notification
{
    // start timer to process libevent
    mTimer = [NSTimer scheduledTimerWithTimeInterval:0.1 target:self selector:@selector(onTimer:) userInfo:nil repeats:YES];

    // add handler
    CSSchemeFactory::Register();
    
    CSWindow *window = new CSWindow();
    window->Show(true);
}

-(void) applicationWillTerminate:(NSNotification *)notification
{
    // stop the timer
    [mTimer invalidate];
}


-(void) onTimer:(NSTimer *)timer
{
    event_loop(EVLOOP_ONCE);
}

@end
