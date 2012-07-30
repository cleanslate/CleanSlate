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
