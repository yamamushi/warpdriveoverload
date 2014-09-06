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
#include <stdlib.h>

#include "bresenham2d.h"

ncursesWindow::ncursesWindow(int height, int length, int ypos, int xpos) : m_height(height), m_length(length), m_ypos(ypos), m_xpos(xpos)
{
    
    m_window = newwin(height, length, ypos, xpos);
    m_border = _SharedPtr<winBorder>(new winBorder);
    
    m_showBorder = true;
    setborder('|', '|', '=', '=', '+', '+', '+', '+');
    
    setBorderColorfg(COLOR_BLUE);
    setBorderColorbg(COLOR_BLACK);
    setBorderColor(getBorderColorfg(), getBorderColorbg());
    
    setBGColor(COLOR_BLACK);
    setFGColor(COLOR_GREEN);
    setNormalColor(getFGColor(), getBGColor());
    
    
    setCursorColorfg(COLOR_BLUE);
    setCursorColorbg(COLOR_BLACK);
    setCursorColor(getCursorColorfg(), getCursorColorbg());
    
    
    setSelectedColorfg(COLOR_RED);
    setSelectedColorbg(COLOR_BLACK);
    setSelectedColor(getSelectedColorfg(), getSelectedColorbg());
    
    
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
    
    drawBorder();

}



void ncursesWindow::drawBorder(){
    
    if(m_showBorder){
        
        wattrset(m_window, COLOR_PAIR(m_borderColor));
        wborder(m_window, m_border->m_ls, m_border->m_rs, m_border->m_ts, m_border->m_bs, m_border->m_tl, m_border->m_tr, m_border->m_bl, m_border->m_br);
        wattroff(m_window, COLOR_PAIR(m_borderColor));
    }
    
}

void ncursesWindow::render(){
    
    for(size_t x = 0; x < m_widgetList.size(); x++){
        m_widgetList.at(x)->render();
    }
    
    drawBorder();
    wrefresh(m_window);
    
}

void ncursesWindow::refresh(){
    
    clearScreen();

    for(size_t x = 0; x < m_widgetList.size(); x++){
        m_widgetList.at(x)->refresh();
    }
    
}

void ncursesWindow::handleKeys(int input){

    // We are going to let our WidgetManager as part of our interface list
	    // Handle keyboard management
    
    /*
    for(size_t x = 0; x < m_menuList.size(); x++){
        m_menuList.at(x)->handleKeys(input);
    }
    
    for(size_t x = 0; x < m_widgetList.size(); x++){
        m_widgetList.at(x)->handleKeys(input);
    } */
    
}


void ncursesWindow::drawAt(int x, int y, std::string output){
    
    wattrset(m_window, COLOR_PAIR(m_normalColor));
    mvwprintw(m_window, y, x, "%s", output.c_str());
    wattroff(m_window, COLOR_PAIR(m_normalColor));
}


void ncursesWindow::drawLine(int x1, int y1, int x2, int y2, std::string symbol, int fg, int bg, int attr){
    
    bresenham2d(x1, y1, x2, y2, _STD_BIND(&ncursesWindow::drawLineCallBack, this, std::placeholders::_1, std::placeholders::_2, symbol, fg, bg, attr)); //STD_BIND(&ncursesWindow::drawAt, this, x1, y1, fg, bg, attr));
    
}

void ncursesWindow::drawLineCallBack(int x, int y, std::string output, int fg, int bg, int attr){
    
    drawAt(x, y, output, fg, bg, attr);
    
}


void ncursesWindow::drawAt(int x, int y, std::string output, int fg, int bg, int attr){
    
    if(x == -1 || y == -1)
        return;
    
    if(fg == 0)
        fg = m_fgColor;
    if(bg == 0)
        bg = m_bgColor;
    
    int paircolor = ColorManager::Instance()->checkColorPair(fg, bg);
    
    wattrset(m_window, COLOR_PAIR(paircolor));
    mvwprintw(m_window, y, x, "%s", output.c_str());
    if(attr > 0){
        mvwchgat(m_window, y, x, output.length(), attr, 0, NULL);
    }
    wattroff(m_window, COLOR_PAIR(paircolor));
}

void ncursesWindow::drawAt(int x, int y, char c){

    wattrset(m_window, COLOR_PAIR(m_normalColor));
    mvwprintw(m_window, y, x, "%c", c);
    wattroff(m_window, COLOR_PAIR(m_normalColor));
}

void ncursesWindow::drawAt(int x, int y, char c, int fg, int bg, int attr){
    
    if(x == -1 || y == -1)
        return;
    
    if(fg == 0)
        fg = m_fgColor;
    if(bg == 0)
        bg = m_bgColor;
    
    
    int paircolor = ColorManager::Instance()->checkColorPair(fg, bg);
    
    wattrset(m_window, COLOR_PAIR(paircolor));
    mvwprintw(m_window, y, x, "%c", c);
    if(attr > 0){
        mvwchgat( m_window, y, x, 1, attr, 0, NULL);
    }
    wattroff(m_window, COLOR_PAIR(m_normalColor));
    
}

void ncursesWindow::setNormalColor(int fg, int bg){
   
    if(fg == 0)
        fg = m_fgColor;
    if(bg == 0)
        bg = m_bgColor;
    
    
    m_normalColor = ColorManager::Instance()->checkColorPair(fg, bg);
    
}


void ncursesWindow::setSelectedColor(int fg, int bg){
    
    if(fg == 0)
        fg = m_fgColor;
    if(bg == 0)
        bg = m_bgColor;
    
    
    m_selectedColor = ColorManager::Instance()->checkColorPair(fg, bg);
    
}


void ncursesWindow::setCursorColor(int fg, int bg){
    
    if(fg == 0)
        fg = m_fgColor;
    if(bg == 0)
        bg = m_bgColor;
    
    
    m_cursorColor = ColorManager::Instance()->checkColorPair(fg, bg);
}

void ncursesWindow::setBorderColor(int fg, int bg){
    
    if(fg == 0)
        fg = m_fgColor;
    if(bg == 0)
        bg = m_bgColor;
    
    
    m_borderColor = ColorManager::Instance()->checkColorPair(fg, bg);
    
}


void ncursesWindow::putPixel(_SharedPtr<Pixel> point){
    
    if(point->x == -1 || point->y == -1)
        return;
    
    int l_fg, l_bg;
    int l_attr;
    
    l_attr = point->attr;
    l_fg = point->fg;
    l_bg = point->bg;
    
    if(l_fg == 0)
        l_fg = m_fgColor;
    if(l_bg == 0)
        l_bg = m_bgColor;
    
    int paircolor = ColorManager::Instance()->checkColorPair(l_fg, l_bg);
    
    wattrset(m_window, COLOR_PAIR(paircolor));
    
    mvwprintw(m_window, point->y, point->x, "%s", point->s.c_str());
    if(l_attr > 0)
        mvwchgat(m_window, point->y, point->x, point->s.length(), point->attr, paircolor, NULL);
    
    wattroff(m_window, COLOR_PAIR(paircolor));
    
}



void ncursesWindow::addWidget(_SharedPtr<Widget> target){
    
    removeWidget(target);
    target->setParent(shared_from_this());
    m_widgetList.push_back(target);
    
}


void ncursesWindow::clearRow(int row, int from){
    
    if(row < 0 || row > m_height)
        return;
    
    for(int x = from; x < m_length; x++){
        
        drawAt(x, row, " ");
        
    }
    
}

void ncursesWindow::clearColumn(int column, int from){
    
    if(column < 0 || column > m_length)
        return;
    
    for(int x = from; x < m_height; x++){
        
        drawAt(column, x, " ");
        
    }
}


void ncursesWindow::removeWidget(_SharedPtr<Widget> target){
    
    std::vector<_SharedPtr<Widget> >::iterator it = std::find(m_widgetList.begin(), m_widgetList.end(), target);
    if (it != m_widgetList.end()){
        m_widgetList.erase(std::remove(m_widgetList.begin(), m_widgetList.end(), target), m_widgetList.end());
    }
    
    
}

