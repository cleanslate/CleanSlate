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
#import "AppDelegate.h"

#include "include/cef_app.h"
#include "include/cef_client.h"

#include "event.h"

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
    
    event_init();

    /*
    while (1)
    {
        event_loop(EVLOOP_ONCE);
        CefDoMessageLoopWork();
        
        // sleep 20ms
        usleep(20000);        
    }
     */
    
    CefRunMessageLoop();
    
    [pool drain];
    
    return EXIT_SUCCESS;
}
