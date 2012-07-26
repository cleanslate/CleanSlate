//
//  CSView.m
//  CleanSlate
//
//  Created by Yulius Tjahjadi on 7/22/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "CSView.h"

#import "CSWindowImpl.h"

#include "CSBrowserClient.h"

@implementation CSView

-(id) initWithFrame:(NSRect)frame
{
    if ((self = [super initWithFrame:frame]))
    {
        // Initialization code here.
        [[self window] setHasShadow:NO];
        [[self window] setHasShadow:YES];
                
        mBrowserClient = NULL;
    }
    
    return self;
}

-(void) dealloc
{
    [super dealloc];
}

-(void) setBrowserClient:(CSBrowserClient *)client
{
    mBrowserClient = client;
}

-(void) drawRect:(NSRect)dirtyRect
{
    // Drawing code here.
    [[NSColor grayColor] set];
    NSRectFill([self frame]);

    if (mBrowserClient)
    {
        CSBrowserClient::Image &image = mBrowserClient->GetBrowserImage();
        int width, height;
        mBrowserClient->GetBrowserSize(width, height);
        if (width > 0 && height > 0)
        {
            //NSBitmapImageRep *bitmap = [NSBitmapImageRep imageRepWithData:data];
            unsigned char *data = &image.front();
            NSBitmapImageRep *bitmap = [[[NSBitmapImageRep alloc] initWithBitmapDataPlanes:&data pixelsWide:width pixelsHigh:height bitsPerSample:8 samplesPerPixel:4 hasAlpha:YES isPlanar:NO colorSpaceName:NSDeviceRGBColorSpace  bytesPerRow:width*4 bitsPerPixel:32] autorelease];
            
            
            NSImage *nsImage = [[[NSImage alloc] init] autorelease];
            [nsImage addRepresentation:bitmap];
            [nsImage compositeToPoint:NSZeroPoint operation:NSCompositeCopy];
        }
    }
    
    //[image compositeToPoint:NSZeroPoint operation:NSCompositeCopy];
    
    //[[self window] display];
    //[[self window] setHasShadow:NO];
    //[[self window] setHasShadow:YES];
}

@end
