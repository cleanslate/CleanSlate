//
//  AppDelegate.m
//  CleanSlate
//
//  Created by Yulius Tjahjadi on 7/20/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//
#import "AppDelegate.h"

@implementation AppDelegate

-(id) init
{
    if (self = [super init])
    {
        // allocate and initialize window and stuff here ..
        window = [[[NSWindow alloc] init] autorelease];
    }
    return self;
}

-(void) dealloc
{
    [window release];
    [super dealloc];
}

-(void) applicationWillFinishLaunching:(NSNotification *)notification
{
    [window makeKeyAndOrderFront:self];
}

@end
