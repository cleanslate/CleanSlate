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


#import "CSJsMenuItem.h"

@implementation CSJsMenuItem

-(id) initWithTitle:(NSString *)aString keyEquivalent:(NSString *)charCode callback:(CefV8Value *)callback context:(CefV8Context *)context
{
    if ((self = [super initWithTitle:aString action:@selector(onMenu:) keyEquivalent:charCode]))
    {
        [self setTarget:self];
        mContext = context;
        mCallback = callback;
    }
    return self;
}

-(void) dealloc
{
    mCallback = NULL;
    mContext = NULL;
    [super dealloc];
}

-(void) onMenu:(id)sender
{
    if (mCallback.get() && mContext.get())
    {
        CefV8ValueList args;
        CefRefPtr<CefV8Value> retval;
        CefRefPtr<CefV8Exception> exception;     
        
        mCallback->ExecuteFunctionWithContext(mContext, NULL, args, retval, exception, false);
    }
}

@end
