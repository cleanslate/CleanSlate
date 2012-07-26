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
    if ((self = [super initWithContentRect:NSMakeRect(100,100,400,300)
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
        [self setContentView:view];
        
    }
    return self;
}

-(BOOL) canBecomeKeyWindow
{
    return YES;
}

-(void) mouseDown:(NSEvent *)theEvent
{
    initialLocation = [theEvent locationInWindow];
}

-(void) mouseDragged:(NSEvent *)theEvent 
{
    NSRect screenVisibleFrame = [[NSScreen mainScreen] visibleFrame];
    NSRect windowFrame = [self frame];
    NSPoint newOrigin = windowFrame.origin;
    
    // Get the mouse location in window coordinates.
    NSPoint currentLocation = [theEvent locationInWindow];
    // Update the origin with the difference between the new mouse location and the old mouse location.
    newOrigin.x += (currentLocation.x - initialLocation.x);
    newOrigin.y += (currentLocation.y - initialLocation.y);
    
    // Don't let window get dragged up under the menu bar
    if ((newOrigin.y + windowFrame.size.height) > (screenVisibleFrame.origin.y + screenVisibleFrame.size.height)) {
        newOrigin.y = screenVisibleFrame.origin.y + (screenVisibleFrame.size.height - windowFrame.size.height);
    }
    
    // Move the window to the new location
    [self setFrameOrigin:newOrigin];
}

@end
