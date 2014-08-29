//
//  menu.cpp
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 8/28/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//

#include "menu.h"
#include <algorithm>
#include <iostream>

ncursesMenu::ncursesMenu(std::vector<std::pair<std::string, _STD_FUNCTION(void())> > menuList, std::string name, _SharedPtr<ncursesWindow> parent, bool horizontal) : m_name(name), m_menuList(menuList), m_horizontal(horizontal){
    
    m_border = _SharedPtr<winBorder>(new winBorder);
    setParent(parent);
    setAlignment();
    
    m_hidden = false;
    m_selected = 0;
    m_showBorder = true;
    m_menuSize = menuList.size();
    m_showTitle = true;
    m_highlightTitle = true;
    m_subMenuOpen = 0;
    
    init_pair(1, COLOR_GREEN, COLOR_BLACK); // A default Background Color
    setBGColor(COLOR_BLACK);
    setFGColor(COLOR_GREEN);
    setNormalColor(1);
    
    init_pair(2, COLOR_BLUE, COLOR_BLACK); // A default Background Color
    setCursorColor(2);
    
    init_pair(3, COLOR_RED, COLOR_BLACK); // A default Background Color
    setSelectedColor(3);
    
    init_pair(4, COLOR_RED, COLOR_BLACK); // A default Background Color
    setBorderColor(4);
    
    
    
    m_ypos = 0;
    m_xpos = 0;
    
    m_width = 0;
    m_height = 0;
    setHorizontal(horizontal);
    
    
}

void ncursesMenu::setHorizontal(bool option){
    m_horizontal = option;
    resize();
}

void ncursesMenu::resize(){
    
    if(!m_horizontal){
        m_width = m_name.length()+2;
        m_height = m_menuList.size()+1;
        for(size_t x = 0; x < m_menuList.size(); x++){
            if(m_menuList.at(x).first.length()+2 > m_width){
                m_width = m_menuList.at(x).first.length()+2;
            }
        }
    }
    
    else{
        for(size_t x = 0; x < m_menuList.size(); x++){
            m_width += m_menuList.at(x).first.length()+1;
        }
        if(m_showTitle){
            m_width += m_name.length();
        }
        m_width += 2;
        m_height = 3;
    }
    
}


void ncursesMenu::move(int ypos, int xpos){
    
    m_ypos = ypos;
    m_xpos = xpos;
    
}

void ncursesMenu::showBorder(bool show){
    m_showBorder = show;
}


void ncursesMenu::setborder(char ls, char rs, char ts, char bs, char tl, char tr, char bl, char br){
    
    m_border->m_ls = ls;
    m_border->m_rs = rs;
    m_border->m_ts = ts;
    m_border->m_bs = bs;
    m_border->m_tl = tl;
    m_border->m_tr = tr;
    m_border->m_bl = bl;
    m_border->m_br = br;
    
}

void ncursesMenu::setAlignment(menuAlignment align){
    
    m_alignment = align;
    
}


void ncursesMenu::render(){
    
    int charCounter = 0;
    
    for(size_t x = 0; x < m_subMenuList.size(); x++){
        if(!m_subMenuList.at(x).first->getHidden()){
            m_subMenuOpen = m_subMenuList.at(x).second;
            m_subMenuList.at(x).first->render();
        }
    }
    
    if(!m_hidden){
        
        // Parent Window!!
        
        
        if(m_parent){
            
            
            if(m_horizontal){
                wattrset(m_parent->get(), m_normalColor);
                for(size_t x = 0; x < m_menuList.size(); x++){
                    
                    if(x == m_selected){
                        wattron(m_parent->get(), A_REVERSE);
                    }
                    else{
                        wattroff(m_parent->get(), A_REVERSE);
                    }
                    
                    // Show Title?
                    if(x == 0 && m_showTitle){
                        
                        if(m_highlightTitle){
                            wattron(m_parent->get(), A_REVERSE);
                        }
                        else{
                            wattroff(m_parent->get(), A_REVERSE);
                        }
                        mvwprintw(m_parent->get(), m_ypos+1, m_xpos+charCounter+1, "%s", m_name.c_str());
                        charCounter += m_name.length()+1;
                        wattroff(m_parent->get(), A_REVERSE);
                        
                    }
                    
                    
                    
                    if(x == m_selected-1){
                        wattrset(m_parent->get(), m_cursorColor);
                    }
                    else{
                        wattrset(m_parent->get(), m_normalColor);
                    }
                    
                    for(int i = 0; i < m_selectedList.size(); i++){
                        if(x+1 == m_selectedList.at(i)){
                            wattrset(m_parent->get(), COLOR_PAIR(3));
                        }
                        if(x+1 == m_selectedList.at(i) && x == m_selected-1){
                            wattrset(m_parent->get(), m_cursorColor);
                        }
                    }
                    
                    // Here we are printing the item out
                    if( x < m_menuList.size()){
                        mvwprintw(m_parent->get(), m_ypos+1, m_xpos+charCounter+1, "%s", m_menuList.at(x).first.c_str());
                        charCounter += m_menuList.at(x).first.length()+1;
                    }
                    
                    
                }
                if(m_showBorder){
                    
                    wattrset(m_parent->get(), m_borderColor);
                    
                    for(size_t line = 0; line < m_width; line++){
                        mvwprintw(m_parent->get(), m_ypos, line, "%c", m_border->m_ts);
                        mvwprintw(m_parent->get(), m_ypos+2, line, "%c", m_border->m_bs);
                        
                    }
                    
                    mvwprintw(m_parent->get(), m_ypos, m_xpos, "%c", m_border->m_tl);
                    mvwprintw(m_parent->get(), m_ypos, m_xpos+m_width, "%c", m_border->m_tr);
                    mvwprintw(m_parent->get(), m_ypos+1, m_xpos, "%c", m_border->m_ls);
                    mvwprintw(m_parent->get(), m_ypos+1, m_xpos+m_width, "%c", m_border->m_rs);
                    
                    mvwprintw(m_parent->get(), m_ypos+2, m_xpos, "%c", m_border->m_bl);
                    mvwprintw(m_parent->get(), m_ypos+2, m_xpos+m_width, "%c", m_border->m_br);
                    
                }
            }
            
            
            else{
                wattrset(m_parent->get(), m_normalColor);
                for(size_t x = 0; x < m_menuList.size()+1; x++){
                    //wattron(m_parent->get(), COLOR_PAIR(m_normalColor)); // Set the background color accordingly
                    //                    wattroff(m_parent->get(), A_REVERSE);
                    if(x == 0){
                        if(m_showTitle){
                            if(m_highlightTitle){
                                wattron(m_parent->get(), A_REVERSE);
                            }
                            else{
                                wattroff(m_parent->get(), A_REVERSE);
                            }
                            mvwprintw(m_parent->get(), m_ypos, m_xpos + ((m_width)/2) - (m_name.length()/2), "%s", m_name.c_str());
                            wattroff(m_parent->get(), A_REVERSE);
                        }
                        //wattroff(m_parent->get(), A_REVERSE);
                        
                    }
                    //wattroff(m_parent->get(), A_REVERSE);
                    
                    
                    if(m_showBorder){
                        
                        wattrset(m_parent->get(), m_borderColor);
                        for(size_t line = 0; line < m_width; line++){
                            if(m_showTitle){
                                if((line < (m_xpos + ((m_width)/2) - (m_name.length()/2))) || (line > (m_xpos + ((m_width)/2) + (m_name.length()/2))) ) {
                                    mvwprintw(m_parent->get(), m_ypos, line+m_xpos, "%c", m_border->m_ts);
                                }
                            }
                            else{
                                mvwprintw(m_parent->get(), m_ypos, line, "%c", m_border->m_ts);
                            }
                        }
                        
                        mvwprintw(m_parent->get(), m_ypos, m_xpos, "%c", m_border->m_tl);
                        mvwprintw(m_parent->get(), m_ypos, m_xpos+m_width, "%c", m_border->m_tr);
                        
                    }
                    
                    
                    if(x == m_selected-1){
                        wattrset(m_parent->get(), m_cursorColor);
                    }
                    else{
                        wattrset(m_parent->get(), m_normalColor);
                    }
                    
                    
                    for(int i = 0; i < m_selectedList.size(); i++){
                        if(x+1 == m_selectedList.at(i)){
                            wattrset(m_parent->get(), COLOR_PAIR(3));
                        }
                        if(x+1 == m_selectedList.at(i) && x == m_selected-1){
                            wattrset(m_parent->get(), m_cursorColor);
                        }
                    }
                    
                    
                    
                    // Here we are printing the item out
                    if( x < m_menuList.size()){
                        mvwprintw(m_parent->get(), m_ypos+1+x, m_xpos+1, "%s", m_menuList.at(x).first.c_str());
                    }
                    
                    wattroff(m_parent->get(), A_REVERSE);
                    
                    if(m_showBorder){
                        
                        wattrset(m_parent->get(), m_borderColor);
                        if(x != 0){
                            mvwprintw(m_parent->get(), m_ypos+x, m_xpos, "%c", m_border->m_ls);
                            mvwprintw(m_parent->get(), m_ypos+x, m_xpos+m_width, "%c", m_border->m_rs);
                        }
                    }
                    
                    
                    if( x == m_height-2){
                        wattrset(m_parent->get(), m_normalColor);
                        if(m_showBorder){
                            wattrset(m_parent->get(), m_borderColor);
                            for(size_t line = 0; line < m_width; line++){
                                mvwprintw(m_parent->get(), m_ypos+m_height, line+1+m_xpos, "%c", m_border->m_bs);
                            }
                            mvwprintw(m_parent->get(), m_ypos+m_height, m_xpos, "%c", m_border->m_bl);
                            mvwprintw(m_parent->get(), m_ypos+m_height, m_xpos+m_width, "%c", m_border->m_br);
                        }
                    }
                }
                
                
            }
        }
        
        
        
        // No Parent Window!!!
        
        
        else{
            ;
            
        }
    }
    
}


void ncursesMenu::execute(){
    
    if(m_selected == 0){
        return;
    }
    _STD_FUNCTION(void()) command;
    
    if(m_subMenuOpen){
        m_subMenuList.at(m_subMenuControl-1).first->execute();
        return;
    }
    
    for(size_t x = 0; x < m_subMenuList.size(); x++){
        if(m_subMenuList.at(x).second == m_selected-1){
            toggleSubMenu();
            return;
        }
    }
    
    command = m_menuList.at(m_selected-1).second;
    command();
    
}

void ncursesMenu::setParent(_SharedPtr<ncursesWindow> target){
    
    m_parent = target;
    m_border = target->getBorder();
    
}


int ncursesMenu::getCurrentItem(){
    
    return m_selected;
    
}

void ncursesMenu::addSubMenu(_SharedPtr<ncursesMenu> menu, int keyID){
    
    
    std::pair<_SharedPtr<ncursesMenu>, int> item(menu, keyID-1);
    
    for(size_t x = 0; x < m_subMenuList.size(); x++){
        if(m_subMenuList.at(x).second == keyID-1){
            m_subMenuList.erase(m_subMenuList.begin()+x);
        }
    }
    menu->hide();
    if(m_horizontal){
        int correction = 0;
        if(m_showTitle){
            correction += m_name.length()+1;
        }
        for(size_t x = 0; x < m_menuList.size(); x++){
            if(x < keyID-1){
                correction += m_menuList.at(x).first.length();
            }
        }
        
        menu->move(m_ypos+2, m_xpos+correction+keyID);
    }
    else{
        menu->move(m_ypos+keyID-1, m_xpos+m_width+1);
    }
    menu->setSubMenuStatus(true);
    m_subMenuList.push_back(item);
    
}

void ncursesMenu::toggleSubMenu(){
    
    for(size_t x = 0; x < m_subMenuList.size(); x++){
        if(m_subMenuList.at(x).second == m_selected-1){
            
            m_subMenuList.at(x).first->toggleHide();
            
            if(!m_subMenuList.at(x).first->getHidden())
                m_subMenuList.at(x).first->render();
            
            m_subMenuOpen = !m_subMenuOpen;
            m_subMenuControl = m_subMenuList.at(x).second;
            
            return;
        }
    }
}

void ncursesMenu::toggleItem(int itemID){
    
    std::vector<int>::iterator it = std::find(m_selectedList.begin(), m_selectedList.end(), itemID);
    if (it != m_selectedList.end()){
        m_selectedList.erase(std::remove(m_selectedList.begin(), m_selectedList.end(), itemID), m_selectedList.end());
    }
    else{
        m_selectedList.push_back(itemID);
    }
}


void ncursesMenu::selectNext(){
    
    if(m_subMenuOpen){
        m_subMenuList.at(m_subMenuControl-1).first->selectNext();
        return;
    }
    
    if(m_selected < m_menuSize){
        m_selected++;
    }
    else{
        m_selected = 1;
    }
}

void ncursesMenu::selectPrev(){
    if(m_subMenuOpen){
        m_subMenuList.at(m_subMenuControl-1).first->selectPrev();
        return;
    }
    if(m_selected > 1){
        m_selected--;
    }
    else{
        m_selected = m_menuSize;
    }
}

void ncursesMenu::selectNone(){
    m_selected = 0;
}

void ncursesMenu::closeSubMenu(){
    
    if(m_subMenuOpen){
        
        m_subMenuList.at(m_subMenuControl-1).first->hide();
        m_subMenuOpen = false;
        m_subMenuControl = 0;
        wclear(m_parent->get());
    }
    
}


void ncursesMenu::handleKeys(int input){
    
    if(!m_horizontal){
        switch(input){
            case KEY_DOWN:
                selectNext();
                break;
                
            case KEY_UP:
                selectPrev();
                break;
                
            case KEY_LEFT:
                closeSubMenu();
                break;
                
            case KEY_RIGHT:
                execute();
                break;
            case '\n':
                execute();
        }
    }
    else if(m_horizontal && m_subMenuOpen){
        switch(input){
            case KEY_DOWN:
                selectNext();
                break;
                
            case KEY_UP:
                selectPrev();
                break;
                
            case KEY_LEFT:
                closeSubMenu();
                break;
                
            case KEY_RIGHT:
                execute();
                break;
            case '\n':
                execute();
        }
    }
    else{
        switch(input){
            case KEY_DOWN:
                execute();
                break;
                
            case KEY_UP:
                closeSubMenu();
                break;
                
            case KEY_LEFT:
                selectPrev();
                break;
                
            case KEY_RIGHT:
                selectNext();
                break;
            case '\n':
                execute();
        }
    }
    
}


void ncursesMenu::close(){
    
    if(m_isSubMenu){
        
    }
    
}