//
//  CSView.m
//  CleanSlate
//
//  Created by Yulius Tjahjadi on 7/22/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "CSView.h"

@implementation CSView

-(id) initWithFrame:(NSRect)frame
{
    if ((self = [super initWithFrame:frame]))
    {
        // Initialization code here.
        image = [[NSImage imageNamed:@"rgba8"] retain];
        [[self window] setHasShadow:NO];
        [[self window] setHasShadow:YES];
        
        // resize window
        NSSize size = image.size;
        [[self window] frameRectForContentRect:NSMakeRect(100, 100, size.width, size.height)];
    }
    
    return self;
}

-(void) dealloc
{
    [image release];
    [super dealloc];
}

-(void) drawRect:(NSRect)dirtyRect
{
    // Drawing code here.
    [[NSColor grayColor] set];
    NSRectFill([self frame]);
    
    //[image compositeToPoint:NSZeroPoint operation:NSCompositeCopy];
    
    //[[self window] display];
    //[[self window] setHasShadow:NO];
    //[[self window] setHasShadow:YES];
}

@end
