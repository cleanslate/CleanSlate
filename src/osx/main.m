//
//  main.m
//  CleanSlate
//
//  Created by Yulius Tjahjadi on 7/20/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "AppDelegate.h"

int main(int argc, char *argv[])
{
    NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
    NSApplication * application = [NSApplication sharedApplication];
    
    AppDelegate * appDelegate = [[[AppDelegate alloc] init] autorelease];
    
    [application setDelegate:appDelegate];
    [application run];
    
    [pool drain];
    
    return EXIT_SUCCESS;
}
