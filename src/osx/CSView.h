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
}

-(void) setBrowserClient:(CSBrowserClient *)client;
@end