//
//  window.h
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 8/28/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//

#ifndef __warpdriveoverloaded__window__
#define __warpdriveoverloaded__window__

#include <ncurses.h>
#include <vector>
#include "menu.h"
#include "tr1_wrapper.h"

class ncursesMenu;

class ncursesWindow {
    
public:
    ncursesWindow(int height, int length, int ypos, int xpos);
    
    WINDOW * get(){return m_window;}
    void close();
    
    void addMenu(_SharedPtr<ncursesMenu> target){m_menuList.push_back(target);}
    
    void setborder(char ls, char rs, char ts, char bs, char tl, char tr, char bl, char br);
    
private:
    
    WINDOW *m_window;
    std::vector<_SharedPtr<ncursesMenu>> m_menuList;
    
    
};


#endif /* defined(__warpdriveoverloaded__window__) */
