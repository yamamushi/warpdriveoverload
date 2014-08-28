//
//  menu.cpp
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 8/28/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//

#include "menu.h"


ncursesMenu::ncursesMenu(std::vector<std::string> menuList, std::string name, _SharedPtr<ncursesWindow> parent, bool horizontal) : m_name(name), m_menuList(menuList), m_parent(parent), m_horizontal(horizontal){
    
    m_hidden = false;
    
    m_ypos = 0;
    m_xpos = 0;

}

void ncursesMenu::move(int ypos, int xpos){
    
    m_ypos = ypos;
    m_xpos = xpos;
    
}

void ncursesMenu::render(){
    
    int charCounter = 0;
    if(m_parent){
        if(m_horizontal){
            for(size_t x = 0; x < m_menuList.size(); x++){
        
                if(x == 0){
                    mvwprintw(m_parent->get(), m_ypos+1, m_xpos+charCounter+1, "%s", m_name.c_str());
                    charCounter += m_name.length()+1;

                }
                else{
                    mvwprintw(m_parent->get(), m_ypos+1, m_xpos+charCounter+1, "%s", m_menuList.at(x).c_str());
                    charCounter += m_menuList.at(x).length()+1;

                }
        
            }
        }
        else{
            for(size_t x = 0; x < m_menuList.size(); x++){
                if(x == 0){
                    mvwprintw(m_parent->get(), m_ypos+1, m_xpos+1, "%s", m_name.c_str());

                }
                mvwprintw(m_parent->get(), m_ypos+2+x, m_xpos+1, "%s", m_menuList.at(x).c_str());
                
            }
        }
    }
    else{
        if(m_horizontal){
            for(size_t x = 0; x < m_menuList.size(); x++){
                
                mvwprintw(m_parent->get(), m_ypos+1, m_xpos+charCounter, "%s", m_menuList.at(x).c_str());
                
            }
        }
    }

    
}


void ncursesMenu::hide(){
    
}

void ncursesMenu::show(){
    
}

void ncursesMenu::close(){
    
}