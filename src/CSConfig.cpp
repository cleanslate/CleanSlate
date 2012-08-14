///
//  CSConfig.cpp
//  CleanSlate
//
//  Created by Yulius Tjahjadi on 8/13/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "CSPrecomp.h"

#include "CSConfig.h"
#include "CSWindow.h"

#include "jansson.h"

CSConfig::CSConfig()
{
    
}

CSConfig::~CSConfig()
{
    
}


void CSConfig::LoadConfig(const char *file)
{
    json_error_t error;
    json_t *config = json_load_file(file, JSON_REJECT_DUPLICATES, &error);
    if (config)
    {
        json_t *windows = json_object_get(config, "windows");
        size_t count = json_array_size(windows);
        for (size_t i = 0; i < count; i++)
        {
            json_t *winInfo = json_array_get(windows, i);
            json_t *urlVal = json_object_get(winInfo, "url");
            std::string url = "local://file/";
            url.append(json_string_value(urlVal));
            
            CSWindow *win = new CSWindow(url.c_str());
            win->Show(false);
        }
    }
    else
    {
        CSLogError("JSON: %s:%d - %s", error.source, error.line, error.text);
    }
}
