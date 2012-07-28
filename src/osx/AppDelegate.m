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
    // add handler
    CSSchemeFactory::Register();
    
    
    CSWindow *window = new CSWindow();
    window->Show(true);
    
    //NSWindow *win = [[NSWindow alloc] init];
    //[win makeKeyWindow];
    //[win orderFront:self];
}

@end
