//
//  menu.h
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 8/28/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//

#ifndef __warpdriveoverloaded__menu__
#define __warpdriveoverloaded__menu__

#include <ncurses.h>
#include "window.h"

#include <string>
#include <vector>
#include "tr1_wrapper.h"

class ncursesMenu {
    
public:
    ncursesMenu(std::vector<std::string> menuList, ncursesWindow *m_parent, bool horizontal = false);
    
    WINDOW * getParent(){return m_parent;}
    
    void setHorizontal(bool option){m_horizontal = option;}
    void close();
    
    
private:
    
    WINDOW *m_parent;
    bool m_horizontal;
    std::vector<std::string> m_menuList;
    
    
};
#endif /* defined(__warpdriveoverloaded__menu__) */
