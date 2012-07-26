//
//  main.m
//  CleanSlate
//
//  Created by Yulius Tjahjadi on 7/20/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "AppDelegate.h"

#include "include/cef_app.h"
#include "include/cef_client.h"

int main(int argc, char *argv[])
{
    NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
    NSApplication * application = [NSApplication sharedApplication];
    
    AppDelegate * appDelegate = [[[AppDelegate alloc] init] autorelease];
    
    CefSettings settings;
    CefRefPtr<CefApp> app;
    
    // Initialize CEF.
    CefInitialize(settings, app);
    

    
    
    [application setDelegate:appDelegate];
    [application run];
    
    [pool drain];
    
    return EXIT_SUCCESS;
}
