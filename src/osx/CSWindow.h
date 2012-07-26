//
//  CSWindow.h
//  CleanSlate
//
//  Created by Yulius Tjahjadi on 7/21/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef __CSWINDOW_H__
#define __CSWINDOW_H__

class CSWindow
{
public:
    CSWindow();
    ~CSWindow();
    
    void *winHandle();
    void Show(bool show);
    
private:
    void *mWindow;
    
};

#endif
