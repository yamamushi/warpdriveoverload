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

class GraphChart {
    
public:
    
    GraphChart(_SharedPtr<ncursesWindow> parent) : m_parent(parent){};
    
    _SharedPtr<ncursesWindow> getParent(){return m_parent;}
    
    void fill();
    
private:
    
    _SharedPtr<ncursesWindow> m_parent;
    
};


#endif /* defined(__warpdriveoverloaded__graphchart__) */
