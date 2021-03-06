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

#include "CSUtil.h"


std::string CSUtil::GetLocalDir()
{
    NSString *path = [[NSBundle mainBundle] resourcePath];
    return [path UTF8String];
}

std::string CSUtil::GetOS()
{
    return "osx";
}

bool CSUtil::Unlink(const CefString &str)
{
    return unlink(str.ToString().c_str()) == 0;
}