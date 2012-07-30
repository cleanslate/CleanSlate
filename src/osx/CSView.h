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

#import <Cocoa/Cocoa.h>

class CSBrowserClient;

@interface CSView : NSView
{
    CSBrowserClient *mBrowserClient;
    std::vector<unsigned char> mImage;
    NSSize mImageSize;
    
    NSPoint mStartMovePos;
    BOOL mMoving;
    
    NSPoint mStartResizePos;
    NSRect mStartResizeFrame;
    BOOL mResizing;
}

-(void) setBrowserClient:(CSBrowserClient *)client;
-(void) updateRect:(unsigned char *)buffer size:(NSSize)size rect:(NSRect)rect;

-(void) startMove;
-(void) stopMove;
-(void) startResize;
-(void) stopResize;
-(void) setSize:(NSSize)size;
@end
