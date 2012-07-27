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
}

-(void) setBrowserClient:(CSBrowserClient *)client;
-(void) updateRect:(unsigned char *)buffer size:(NSSize)size rect:(NSRect)rect;
@end
