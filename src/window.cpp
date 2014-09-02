//
//  window.cpp
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 8/28/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//

#include "window.h"
#include "tr1_threading.h"
#include "tr1_wrapper.h"
#include <iostream>
#include <algorithm>

ncursesWindow::ncursesWindow(int height, int length, int ypos, int xpos) : m_height(height), m_length(length), m_ypos(ypos), m_xpos(xpos)
{
    
    m_window = newwin(height, length, ypos, xpos);
    m_border = _SharedPtr<winBorder>(new winBorder);
    
    m_showBorder = true;
    
    setborder('|', '|', '=', '=', '+', '+', '+', '+');
    
    
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
    
}


void ncursesWindow::resize(int height, int length, int ypos, int xpos){

    m_height = height;
    m_length = length;
    m_ypos = ypos;
    m_xpos = xpos;
    delwin(m_window);
    m_window = newwin(height, length, ypos, xpos);
}

void ncursesWindow::close(){
    
    if(m_window){
        /* box(local_win, ' ', ' '); : This won't produce the desired
         * result of erasing the window. It will leave it's four corners
         * and so an ugly remnant of window.
         */
        wborder(m_window, ' ', ' ', ' ',' ',' ',' ',' ',' ');
        wrefresh(m_window);
        delwin(m_window);
    
    }
    else{
        //std::cerr << "Attempted to close null window!" << std::endl;
    }
}

void ncursesWindow::closeAllMenus(){
    
    for(size_t x = 0; x < m_menuList.size(); x++){
        m_menuList.at(x)->closeSubMenu();
    }
    
}

void ncursesWindow::clearScreen(){
    
    wclear(get());

}

void ncursesWindow::setborder(char ls, char rs, char ts, char bs, char tl, char tr, char bl, char br){

    m_border->m_ls = ls;
    m_border->m_rs = rs;
    m_border->m_ts = ts;
    m_border->m_bs = bs;
    m_border->m_tl = tl;
    m_border->m_tr = tr;
    m_border->m_bl = bl;
    m_border->m_br = br;
    
    if(m_showBorder)
        wborder(m_window, ls, rs, ts, bs, tl, tr, bl, br);

}


void ncursesWindow::drawBorder(){
    
    if(m_showBorder)
        wborder(m_window, m_border->m_ls, m_border->m_rs, m_border->m_ts, m_border->m_bs, m_border->m_tl, m_border->m_tr, m_border->m_bl, m_border->m_br);
            
}

void ncursesWindow::render(){
    
    for(size_t x = 0; x < m_widgetList.size(); x++){
        m_widgetList.at(x)->render();
    }
    
    for(size_t x = 0; x < m_menuList.size(); x++){
        m_menuList.at(x)->render();
    }
    drawBorder();
    wrefresh(m_window);
    
}

void ncursesWindow::refresh(){
    
    clearScreen();

    for(size_t x = 0; x < m_widgetList.size(); x++){
        m_widgetList.at(x)->refresh();
    }
    drawBorder();
    wrefresh(m_window);
}

void ncursesWindow::handleKeys(int input){

    for(size_t x = 0; x < m_menuList.size(); x++){
        m_menuList.at(x)->handleKeys(input);
    }
    
    for(size_t x = 0; x < m_widgetList.size(); x++){
        m_widgetList.at(x)->handleKeys(input);
    }
    
}

void ncursesWindow::drawAt(int x, int y, std::string output){
    
    mvwprintw(m_window, y, x, "%s", output.c_str());

}


void ncursesWindow::drawAt(int x, int y, char c){
    
    mvwprintw(m_window, y, x, "%c", c);
    
}


void ncursesWindow::addWidget(_SharedPtr<Widget> target){
    
    removeWidget(target);
    target->setParent(shared_from_this());
    m_widgetList.push_back(target);
    
}


void ncursesWindow::removeWidget(_SharedPtr<Widget> target){
    
    std::vector<_SharedPtr<Widget> >::iterator it = std::find(m_widgetList.begin(), m_widgetList.end(), target);
    if (it != m_widgetList.end()){
        m_widgetList.erase(std::remove(m_widgetList.begin(), m_widgetList.end(), target), m_widgetList.end());
    }
    
    
}

