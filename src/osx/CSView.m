//
//  CSView.m
//  CleanSlate
//
//  Created by Yulius Tjahjadi on 7/22/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "CSView.h"

#import "CSWindowImpl.h"

#include "CSBrowserClient.h"

@implementation CSView

-(id) initWithFrame:(NSRect)frame
{
    if ((self = [super initWithFrame:frame]))
    {
        // Initialization code here.
        [[self window] setHasShadow:NO];
        [[self window] setHasShadow:YES];
        
        
        // create tracking area to capture mouse moves
        NSTrackingAreaOptions options = NSTrackingMouseMoved |
                                        NSTrackingActiveInActiveApp |
                                        NSTrackingInVisibleRect;
        NSTrackingArea *trackingArea = [[NSTrackingArea alloc] initWithRect:frame 
                                                                    options:options
                                                                      owner:self 
                                                                   userInfo:nil];
        [self addTrackingArea:trackingArea];
        
        mBrowserClient = NULL;
        mMoving = NO;
        mResizing = NO;
    }
    
    return self;
}

-(void) dealloc
{
    [super dealloc];
}

-(void) setBrowserClient:(CSBrowserClient *)client
{
    mBrowserClient = client;
}

-(void) updateRect:(unsigned char *)buffer size:(NSSize)size rect:(NSRect)rect
{
    int width = size.width;
    int height = size.height;
    
    mImageSize = size;
    
    if (mImage.size() != width*height*4)
        mImage.resize(width*height*4);
    
    //if (mImageSize != [self frame].size)
    
    for (int y = rect.origin.y; y < rect.origin.y + rect.size.height; y++)
    {
        int offset = (y*width + rect.origin.x) * 4;
        unsigned char *dst = &mImage[offset];
        const unsigned char *src = &buffer[offset];
        for (int x = rect.origin.x; x < rect.origin.x + rect.size.width; x++)
        {
            dst[0] = src[2]; // R
            dst[1] = src[1]; // G
            dst[2] = src[0]; // B
            dst[3] = src[3]; // A
         
            dst += 4;
            src += 4;
        }
    }
    
    NSWindow *window = [self window];
    NSRect frame = [window frame];
    if (frame.size.width != mImageSize.width || 
        frame.size.height != mImageSize.height)
    {
        float diff = frame.size.height - mImageSize.height;
        frame.size.width = mImageSize.width;
        frame.size.height = mImageSize.height; 
        frame.origin.y += diff;
        
        [window setFrame:frame display:YES];
    }
}

-(void) startMove
{    
    mStartMovePos = [NSEvent mouseLocation];
    mMoving = YES;
    CSLogDebug("startMove %f x %f", mStartMovePos.x, mStartMovePos.y);
}

-(void) stopMove
{
    mMoving = NO;
}

-(void) startResize
{
    mStartResizePos = [NSEvent mouseLocation];
    mStartResizeFrame = [[self window] frame];
    mResizing = YES;
    CSLogDebug("startMove %f x %f", mStartResizePos.x, mStartResizePos.y);
}

-(void) stopResize
{
    mResizing = NO;
}

-(void) setSize:(NSSize)size
{
    if (mBrowserClient && mBrowserClient->GetBrowser().get())
        mBrowserClient->GetBrowser()->SetSize(PET_VIEW, size.width, size.height);
}

-(void) drawRect:(NSRect)dirtyRect
{
    // Drawing code here.
    //[[NSColor grayColor] set];
    //NSRectFill([self frame]);

    if (mBrowserClient)
    {
        //int width, height;
        //mBrowserClient->GetBrowserSize(width, height);
        //if (width > 0 && height > 0 && mImage.size() == width*height*4)
        int width = mImageSize.width;
        int height = mImageSize.height;
        {
            NSRect frame = [self frame];
            
            unsigned char *data = &mImage.front();
            NSBitmapImageRep *bitmap = [[[NSBitmapImageRep alloc] initWithBitmapDataPlanes:&data pixelsWide:width pixelsHigh:height bitsPerSample:8 samplesPerPixel:4 hasAlpha:YES isPlanar:NO colorSpaceName:NSDeviceRGBColorSpace  bytesPerRow:width*4 bitsPerPixel:32] autorelease];
            
            
            //NSPoint pt = NSMakePoint(0, frame.size.height - height);
            
            NSImage *nsImage = [[[NSImage alloc] init] autorelease];
            [nsImage addRepresentation:bitmap];
            [nsImage compositeToPoint:NSZeroPoint operation:NSCompositeCopy];
            
            //[self setImage:nsImage];
            /*
            if ([[self window] hasShadow])
            {
                [[self window] setHasShadow:NO];
                [[self window] setHasShadow:YES];
            }
             */
        }
    }
}

-(NSPoint) getClickPointForEvent:(NSEvent*)event
{
    NSPoint windowLocal = [event locationInWindow];
    NSPoint contentLocal = [self convertPoint:windowLocal fromView:nil];
    int x = contentLocal.x;
    int y = [self frame].size.height - contentLocal.y;  // Flip y.
    
    NSPoint pt = {x, y};
    return pt;
}


// mouse events
-(void) mouseEvent:(NSEvent *)event type:(CefBrowser::MouseButtonType)type clickRelease:(BOOL)clickRelease
{
    if (!mBrowserClient || !mBrowserClient->GetBrowser().get())
        return;
    
    NSPoint point = [self getClickPointForEvent:event];
    int clickCount = [event clickCount];
    
    mBrowserClient->GetBrowser()->SendMouseClickEvent(point.x, point.y, type, clickRelease, clickCount);    
}

-(void) mouseDown:(NSEvent *)event
{
    [self mouseEvent:event type:MBT_LEFT clickRelease:false];
}

-(void) rightMouseDown:(NSEvent *)event
{
    [self mouseEvent:event type:MBT_RIGHT clickRelease:false];
}

-(void) otherMouseDown:(NSEvent *)event
{
    [self mouseEvent:event type:MBT_MIDDLE clickRelease:false];
}

-(void) mouseUp:(NSEvent *)event
{
    mMoving = NO;
    mResizing = NO;
    [self mouseEvent:event type:MBT_LEFT clickRelease:true];    
}

-(void) rightMouseUp:(NSEvent *)event
{
    [self mouseEvent:event type:MBT_RIGHT clickRelease:true];    
}

-(void) otherMouseUp:(NSEvent *)event
{
    [self mouseEvent:event type:MBT_MIDDLE clickRelease:true];    
}

-(void) mouseMoved:(NSEvent *)event
{
    if (mMoving)
    {
        // handle window drag   
        NSWindow *window = [self window];
        NSRect screenVisibleFrame = [[NSScreen mainScreen] visibleFrame];
        NSRect windowFrame = [window frame];
        NSPoint newOrigin = windowFrame.origin;
        
        // Get the mouse location in window coordinates.
        NSPoint currentLocation = [NSEvent mouseLocation];
        
        // Update the origin with the difference between the new mouse location and the old mouse location.
        newOrigin.x += (currentLocation.x - mStartMovePos.x);
        newOrigin.y += (currentLocation.y - mStartMovePos.y);
        
        mStartMovePos = currentLocation;
        
        [window setFrameOrigin:newOrigin];
        
        return;
    }
    
    if (mResizing)
    {
        // Get the mouse location in window coordinates.
        NSPoint currentLocation = [NSEvent mouseLocation];
        
        NSSize newSize;
        newSize.width = mStartResizeFrame.size.width + (currentLocation.x - mStartResizePos.x);
        newSize.height = mStartResizeFrame.size.height - (currentLocation.y - mStartResizePos.y);        
        
        if (mBrowserClient)
            mBrowserClient->SetBrowserSize(newSize.width, newSize.height);
        
        return;        
    }
    
    if (!mBrowserClient || !mBrowserClient->GetBrowser().get())
        return;
    
    NSPoint point = [self getClickPointForEvent:event];
    mBrowserClient->GetBrowser()->SendMouseMoveEvent(point.x, point.y, false);    
}

-(void) mouseDragged:(NSEvent *)event
{
    [self mouseMoved:event];
}

-(void)rightMouseDragged:(NSEvent *)event
{
    [self mouseMoved:event];
}

-(void)otherMouseDragged:(NSEvent *)event
{
    [self mouseMoved:event];
}

-(void) mouseEntered:(NSEvent *)event
{
    [self mouseMoved:event];
}

-(void) mouseExited:(NSEvent *)event
{
    if (!mBrowserClient || !mBrowserClient->GetBrowser().get())
        return;
    
    NSPoint point = [self getClickPointForEvent:event];
    
    mBrowserClient->GetBrowser()->SendMouseMoveEvent(point.x, point.y, true);
}

-(void) scrollWheel:(NSEvent *)event
{
    if (!mBrowserClient || !mBrowserClient->GetBrowser().get())
        return;
        
    CGEventRef cgEvent = [event CGEvent];
    
    NSPoint point = [self getClickPointForEvent:event];
    int deltaX = CGEventGetIntegerValueField(cgEvent, kCGScrollWheelEventPointDeltaAxis2);    
    int deltaY = CGEventGetIntegerValueField(cgEvent, kCGScrollWheelEventPointDeltaAxis1);
    
    mBrowserClient->GetBrowser()->SendMouseWheelEvent(point.x, point.y, deltaX, deltaY);
}


// focus
-(BOOL) canBecomeKeyView
{
    if (!mBrowserClient || !mBrowserClient->GetBrowser().get())
        return NO;
    return YES;
}

-(BOOL) acceptsFirstResponder
{
    if (!mBrowserClient || !mBrowserClient->GetBrowser().get())
        return NO;
    return YES;
}

-(BOOL) becomeFirstResponder
{
    if (!mBrowserClient || !mBrowserClient->GetBrowser().get())
        return NO;
    
    mBrowserClient->GetBrowser()->SendFocusEvent(true);    
    return [super becomeFirstResponder];
}

-(BOOL) resignFirstResponder
{
    if (!mBrowserClient || !mBrowserClient->GetBrowser().get())
        return NO;
    
    mBrowserClient->GetBrowser()->SendFocusEvent(false);    
    return [super resignFirstResponder];
}

// keyboard
-(void) getKeyInfo:(CefKeyInfo&)info forEvent:(NSEvent*)event
{
    if ([event type] == NSKeyDown || [event type] == NSKeyUp) {
        NSString* s = [event characters];
        if ([s length] > 0)
            info.character = [s characterAtIndex:0];
        
        s = [event charactersIgnoringModifiers];
        if ([s length] > 0)
            info.characterNoModifiers = [s characterAtIndex:0];
    }
    
    info.keyCode = [event keyCode];
}

-(BOOL)isKeyPadEvent:(NSEvent*)event
{
    if ([event modifierFlags] & NSNumericPadKeyMask)
        return true;
    
    switch ([event keyCode])
    {
        case 71: // Clear
        case 81: // =
        case 75: // /
        case 67: // *
        case 78: // -
        case 69: // +
        case 76: // Enter
        case 65: // .
        case 82: // 0
        case 83: // 1
        case 84: // 2
        case 85: // 3
        case 86: // 4
        case 87: // 5
        case 88: // 6
        case 89: // 7
        case 91: // 8
        case 92: // 9
            return true;
    }
    
    return false;
}

-(BOOL) isKeyUpEvent:(NSEvent*)event
{
    if ([event type] != NSFlagsChanged)
        return [event type] == NSKeyUp;
    
    // FIXME: This logic fails if the user presses both Shift keys at once, for
    // example: we treat releasing one of them as keyDown.
    switch ([event keyCode])
    {
        case 54: // Right Command
        case 55: // Left Command
            return ([event modifierFlags] & NSCommandKeyMask) == 0;
            
        case 57: // Capslock
            return ([event modifierFlags] & NSAlphaShiftKeyMask) == 0;
            
        case 56: // Left Shift
        case 60: // Right Shift
            return ([event modifierFlags] & NSShiftKeyMask) == 0;
            
        case 58: // Left Alt
        case 61: // Right Alt
            return ([event modifierFlags] & NSAlternateKeyMask) == 0;
            
        case 59: // Left Ctrl
        case 62: // Right Ctrl
            return ([event modifierFlags] & NSControlKeyMask) == 0;
            
        case 63: // Function
            return ([event modifierFlags] & NSFunctionKeyMask) == 0;
    }
    return false;
}


-(int) getModifiersForEvent:(NSEvent*)event
{
    int modifiers = 0;
    
    if ([event modifierFlags] & NSControlKeyMask)
        modifiers |= KEY_CTRL;
    if ([event modifierFlags] & NSShiftKeyMask)
        modifiers |= KEY_SHIFT; 
    if ([event modifierFlags] & NSAlternateKeyMask)
        modifiers |= KEY_ALT;
    if ([event modifierFlags] & NSCommandKeyMask)
        modifiers |= KEY_META;
    if ([self isKeyPadEvent:event])
        modifiers |= KEY_KEYPAD;
    
    return modifiers;
}

-(void) keyDown:(NSEvent *)event
{
    if (!mBrowserClient || !mBrowserClient->GetBrowser().get())
        return;
    
    CefKeyInfo keyInfo;
    [self getKeyInfo:keyInfo forEvent:event];
    int modifiers = [self getModifiersForEvent:event];
    
    mBrowserClient->GetBrowser()->SendKeyEvent(KT_KEYDOWN, keyInfo, modifiers);
    
    if ([event modifierFlags] & (NSNumericPadKeyMask | NSFunctionKeyMask))
    {
        // Don't send a Char event for non-char keys like arrows, function keys and
        // clear.
        switch (keyInfo.keyCode)
        {
            case 81: // =
            case 75: // /
            case 67: // *
            case 78: // -
            case 69: // +
            case 76: // Enter
            case 65: // .
            case 82: // 0
            case 83: // 1
            case 84: // 2
            case 85: // 3
            case 86: // 4
            case 87: // 5
            case 88: // 6
            case 89: // 7
            case 91: // 8
            case 92: // 9
                break;
            default:
                return;
        }
    }
    
    mBrowserClient->GetBrowser()->SendKeyEvent(KT_CHAR, keyInfo, modifiers);
}

-(void) keyUp:(NSEvent *)event
{
    if (!mBrowserClient || !mBrowserClient->GetBrowser().get())
        return;

    CefKeyInfo keyInfo;
    [self getKeyInfo:keyInfo forEvent:event];
    int modifiers = [self getModifiersForEvent:event];

    mBrowserClient->GetBrowser()->SendKeyEvent(KT_KEYUP, keyInfo, modifiers);
}

- (void)flagsChanged:(NSEvent *)event {
    if ([self isKeyUpEvent:event])
        [self keyUp:event];
    else
        [self keyDown:event];
}


@end
