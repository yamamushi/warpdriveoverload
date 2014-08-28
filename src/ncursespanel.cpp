//
//  ncursespanel.cpp
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 8/28/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//

#include "ncursespanel.h"


ncursesPanel::ncursesPanel(_SharedPtr<ncursesWindow> child) : m_child(child){
    
    m_panel = new_panel(child->get());
    
}
