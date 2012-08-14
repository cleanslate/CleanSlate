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

#import "AppDelegate.h"

#include "CSWindow.h"
#include "CSSchemeFactory.h"

@implementation AppDelegate

-(id) init
{
    if (self = [super init])
    {

    }
    return self;
}

-(void) dealloc
{
    //[window release];
    [super dealloc];
}

-(void) applicationWillFinishLaunching:(NSNotification *)notification
{
    // start timer to process libevent
    mTimer = [NSTimer scheduledTimerWithTimeInterval:0.1 target:self selector:@selector(onTimer:) userInfo:nil repeats:YES];

    // add handler
    CSSchemeFactory::Register();
    
    
    // TODO: Make this configurable either through plist or something else
    CSWindow *window = new CSWindow("local://file/chat/login.html");
    window->Show(false);
}

-(void) applicationWillTerminate:(NSNotification *)notification
{
    // stop the timer
    [mTimer invalidate];
}


-(void) onTimer:(NSTimer *)timer
{
    event_loop(EVLOOP_ONCE);
}

@end
