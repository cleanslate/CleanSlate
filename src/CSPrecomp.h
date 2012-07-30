#ifdef WIN32
#include <winsock2.h>
#include <Windows.h>

#define close closesocket

#define ftell64(a)     _ftelli64(a)
#define fseek64(a,b,c) _fseeki64(a,b,c)
typedef __int64 off_t;

#else // OSX

#include <sys/socket.h>
#include <netdb.h>
#include <signal.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define ftell64(a)     ftello(a)
#define fseek64(a,b,c) fseeko(a,b,c)
#endif

#ifdef __OBJC__
    #import <Cocoa/Cocoa.h>
#endif


#define SIZEOF_OFF_TYPE    8


#include "include/cef_base.h"
#include "include/cef_app.h"
#include "include/cef_client.h"
#include "include/cef_scheme.h"
#include "include/cef_browser.h"
#include "include/cef_frame.h"

#include "event.h"

#include "CSLog.h"
#include "CSRect.h"
