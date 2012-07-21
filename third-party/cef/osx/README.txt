Chromium Embedded Framework (CEF) Binary Distribution
-------------------------------------------------------------------------------

Date:             July 18, 2012

CEF Version:      1.1084.724
CEF URL:          http://chromiumembedded.googlecode.com/svn/branches/1084/cef1@724

Chromium Verison: 19.0.1084.9
Chromium URL:     http://src.chromium.org/svn/branches/1084/src@130290


This distribution contains all components necessary to build and distribute an
application using CEF. Please see the LICENSING section of this document for
licensing terms and conditions.


CONTENTS
--------

cefclient   Contains the cefclient sample application configured to build
            using the files in this distribution.

Debug       Contains libcef.dylib and other components required to run the debug
            version of CEF-based applications.

docs        Contains C++ API documentation generated from the CEF header files.

include     Contains all required CEF and NPAPI-related header files.  Read
            the include/internal/npapi/README-TRANSFER.txt file for more
            information about the NPAPI-related header files.

libcef_dll  Contains the source code for the libcef_dll_wrapper static library
            that all applications using the CEF C++ API must link against.

Release     Contains libcef.dylib and other components required to run the
            release version of CEF-based applications.

Resources   Contains images and resources required by applications using CEF.
            The contents of this folder should be transferred to the
            Contents/Resources folder in the app bundle.

tools       Scripts that perform post-processing on Mac release targets.


USAGE
-----

Xcode 3 and 4: Open the cefclient.xcodeproj project and build.

Please visit the CEF Website for additional usage information.

http://code.google.com/p/chromiumembedded


REDISTRIBUTION
--------------

This binary distribution contains the below components. Components listed under
the "required" section must be redistributed with all applications using CEF.
Components listed under the "optional" section may be excluded if the related
features will not be used.

Required components:

* CEF core library
    libcef.dylib

* Localized resources
    Resources/*.lproj/
  Note: A .pak file is loaded from this folder based on the value of
  CefSettings.locale. Only configured locales need to be distributed. If no
  locale is configured the default locale of "en" will be used.

* Other resources
    Resources/chrome.pak
    Resources/*.png
    Resources/*.tiff

Optional components:

* FFmpeg audio and video support
    ffmpegsumo.so
  Note: Without this component HTML5 audio and video will not function.


LICENSING
---------

The CEF project is BSD licensed. Please read the LICENSE.txt file included with
this binary distribution for licensing terms and conditions. Other software
included in this distribution is provided under other licenses. Please visit the
below link for complete Chromium and third-party licensing information.

http://code.google.com/chromium/terms.html 
