//
//  CSConfig.h
//  CleanSlate
//
//  Created by Yulius Tjahjadi on 8/13/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef __CSCONFIG_H__
#define __CSCONFIG_H__

class CSConfig
{
public:
    CSConfig();
    ~CSConfig();

    void LoadConfig(const char *file);
};

#endif
