//
//  CSUtil.cpp
//  CleanSlate
//
//  Created by Yulius Tjahjadi on 7/27/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "CSUtil.h"


std::string CSUtil::GetLocalDir()
{
    NSString *path = [[NSBundle mainBundle] resourcePath];
    return [path UTF8String];
}