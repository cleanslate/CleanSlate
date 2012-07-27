//
//  CSWindow.m
//  CleanSlate
//
//  Created by Yulius Tjahjadi on 7/20/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "CSWindowImpl.h"
#import "CSView.h"

@implementation CSWindowImpl

-(id) init
{
    if ((self = [super initWithContentRect:NSMakeRect(0,0,640,480)
                                 styleMask:NSBorderlessWindowMask 
                                   backing:NSBackingStoreBuffered 
                                     defer:NO]))
    {
        [self setStyleMask:NSBorderlessWindowMask];
        [self setBackingType:NSBackingStoreBuffered];
        [self setBackgroundColor:[NSColor clearColor]];
        [self setOpaque:YES];
        
        // create a view
        
        CSView *view = [[[CSView alloc] init] autorelease];
        [view setAutoresizingMask:NSViewWidthSizable | NSViewHeightSizable];
        [self setContentView:view];
        
    }
    return self;
}

-(void) dealloc
{
    [super dealloc];
}

-(BOOL) canBecomeKeyWindow
{
    return YES;
}

@end
