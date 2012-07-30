//
//  CSView.h
//  CleanSlate
//
//  Created by Yulius Tjahjadi on 7/22/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

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
