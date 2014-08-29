//
//  graphchart.h
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 8/28/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//

#ifndef __warpdriveoverloaded__graphchart__
#define __warpdriveoverloaded__graphchart__

#include <ncurses.h>

#include "shell.h"
#include "window.h"
#include "tr1_wrapper.h"
#include "widget.h"

class GraphChart : public Widget {
    
public:
    
    GraphChart(_SharedPtr<ncursesWindow> parent) : Widget(parent){};
    
    void render();
    
    void fill();
    
private:
    
    
};


#endif /* defined(__warpdriveoverloaded__graphchart__) */
