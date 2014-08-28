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

class ncursesWindow;

class ncursesMenu {
    
public:
    ncursesMenu(std::vector<std::string> menuList, std::string m_name, _SharedPtr<ncursesWindow> parent = nullptr, bool horizontal = false);
    
    void setParent(_SharedPtr<ncursesWindow> target){m_parent = target;}
    _SharedPtr<ncursesWindow> getParent(){return m_parent;}
    
    
    void move(int ypos, int xpos);
    void render();
    
    void setHorizontal(bool option){m_horizontal = option;}
    void setborder(char ls, char rs, char ts, char bs, char tl, char tr, char bl, char br);
    
    void hide();
    void show();
    
    void close();
    
    
private:
    
    _SharedPtr<ncursesWindow> m_parent;
    bool m_hidden;
    bool m_horizontal;
    std::vector<std::string> m_menuList;
    int m_xpos;
    int m_ypos;
    
    std::string m_name;
    
    
};
#endif /* defined(__warpdriveoverloaded__menu__) */
