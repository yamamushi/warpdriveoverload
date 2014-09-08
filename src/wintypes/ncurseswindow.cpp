//
//  window.cpp
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 8/28/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//

#include "ncurseswindow.h"
#include "tr1/tr1_threading.h"
#include "tr1/tr1_wrapper.h"
#include <algorithm>
#include <stdlib.h>

#include "graphics/bresenham2d.h"

ncursesWindow::ncursesWindow(int height, int length, int ypos, int xpos) : GenericWindow(height, length, ypos, xpos)
{
    
    //m_window = newwin(height, length, ypos, xpos);
    open();
    
    setBGColor(COLOR_BLACK);
    setFGColor(COLOR_GREEN);
    setNormalColor(getFGColor(), getBGColor());
    
    m_showBorder = true;
    setBorderColorfg(COLOR_BLUE);
    setBorderColorbg(COLOR_BLACK);
    setBorderColor(getBorderColorfg(), getBorderColorbg());
    setborder('|', '|', '=', '=', '+', '+', '+', '+');
    
    
    setCursorColorfg(COLOR_BLUE);
    setCursorColorbg(COLOR_BLACK);
    setCursorColor(getCursorColorfg(), getCursorColorbg());
    
    setSelectedColorfg(COLOR_RED);
    setSelectedColorbg(COLOR_BLACK);
    setSelectedColor(getSelectedColorfg(), getSelectedColorbg());
    
    wrefresh(m_window);
    
    m_open = true;
    
}


void ncursesWindow::resize(int height, int length, int ypos, int xpos){

    if(!m_open)
        return;
    
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

    m_open = false;
    
}




void ncursesWindow::open(){
    
    if(!m_window){
        
        m_window = newwin(m_height, m_length, m_ypos, m_xpos);

    }
    m_open = true;
}

bool ncursesWindow::getOpened(){
    
    return m_open;
}


void ncursesWindow::clearScreen(){
    
    if(!m_open)
        return;
    
    standout();
    wclear(m_window);
    werase(m_window);
    wrefresh(m_window);
    
}



void ncursesWindow::drawBorder(){
    
    if(!m_open)
        return;
    
    if(m_showBorder){
        

        setBorderColor(getBorderColorfg(), getBorderColorbg());
        
        wattrset(m_window, COLOR_PAIR(m_borderColor));
        
        // Just showing how we can use this function to set border attributes
        wborder(m_window, colored_chtype(m_border->m_ls, A_NORMAL, m_borderColor), m_border->m_rs, m_border->m_ts, m_border->m_bs, m_border->m_tl, m_border->m_tr, m_border->m_bl, m_border->m_br);
        
        wattroff(m_window, COLOR_PAIR(m_borderColor));
    }
    
    wrefresh(m_window);
}

int ncursesWindow::colored_chtype(char ch, int attr, int colorPair){
    
    return ((ch) | (attr) | COLOR_PAIR(colorPair));
}

void ncursesWindow::render(){
    
    refresh();
    
    for(size_t x = 0; x < m_widgetList.size(); x++){
        m_widgetList.at(x)->render();
    }
    drawBorder();
}

void ncursesWindow::refresh(){
    
    
    for(size_t x = 0; x < m_widgetList.size(); x++){
        m_widgetList.at(x)->refresh();
    }
}

void ncursesWindow::handleKeys(int input){
    return;
}


void ncursesWindow::drawAt(int x, int y, std::string output){
    
    if(!m_open)
        return;
    
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
    
    if(!m_open)
        return;
    
    if(output == " "){
        drawAt(x, y, ' ', fg, bg, attr);
        return;
    }
    
    if(x == -1 || y == -1)
        return;
    
    if(fg == 0)
        fg = m_fgColor;
    if(bg == 0)
        bg = m_bgColor;
    
    int paircolor = ColorManager::Instance()->checkColorPair(fg, bg);
    
    if(attr == 0)
        attr = A_NORMAL;
    
    wattrset(m_window, attr);
    
    wattrset(m_window, COLOR_PAIR(paircolor));
    mvwprintw(m_window, y, x, "%s", output.c_str());
    if(attr > 0){
        mvwchgat(m_window, y, x, output.length(), attr, 0, NULL);
    }
    wattroff(m_window, COLOR_PAIR(paircolor));
    

}



void ncursesWindow::drawAt(int x, int y, char c){
    
    if(!m_open)
        return;
    
    wattrset(m_window, COLOR_PAIR(m_normalColor));
    mvwprintw(m_window, y, x, "%c", c);
    wattroff(m_window, COLOR_PAIR(m_normalColor));
}

void ncursesWindow::drawAt(int x, int y, char c, int fg, int bg, int attr){
    
    if(!m_open)
        return;
    
    if(x == -1 || y == -1)
        return;
    
    if(fg == 0)
        fg = m_fgColor;
    if(bg == 0)
        bg = m_bgColor;
    
    
    int paircolor = ColorManager::Instance()->checkColorPair(fg, bg);
    
    if(attr == 0)
        attr = A_NORMAL;
    
    wattrset(m_window, attr);
    
    wattrset(m_window, COLOR_PAIR(paircolor));
    mvwprintw(m_window, y, x, "%c", c);
    if(attr > 0){
        mvwchgat( m_window, y, x, 1, attr, 0, NULL);
    }
    wattroff(m_window, COLOR_PAIR(m_normalColor));

    
}

void ncursesWindow::setNormalColor(int fg, int bg){
    
    if(!m_open)
        return;
    
    if(fg == 0)
        fg = m_fgColor;
    if(bg == 0)
        bg = m_bgColor;
    
    
    m_normalColor = ColorManager::Instance()->checkColorPair(fg, bg);
    
    wbkgd(m_window, COLOR_PAIR(m_normalColor)); // Set the background color accordingly
    
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
    
    if(fg < 0)
        fg = m_fgColor;
    if(bg < 0)
        bg = m_bgColor;
    
    
    m_borderColor = ColorManager::Instance()->checkColorPair(fg, bg);
    
}


void ncursesWindow::putPixel(_SharedPtr<Pixel> point){
    
    if(!m_open)
        return;
    
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
    
    
    mvwprintw(m_window, point->y, point->x, "%c", point->c);
    if(l_attr > 0)
        mvwchgat(m_window, point->y, point->x, point->c, point->attr, paircolor, NULL);
    
    wattroff(m_window, COLOR_PAIR(paircolor));
    
    
}





void ncursesWindow::clearArea(int x1, int y1, int x2, int y2){
    
    int beginx, beginy;
    int endx, endy;
    
    if(x1>x2){
        endx = x1;
        beginx = x2;
    }
    else{
        endx = x2;
        beginx = x1;
    }
    
    if(y1 > y2){
        endy = y1;
        beginy = y2;
    }
    else{
        endy = y2;
        beginy = y1;
    }
    
    for(int row = beginy; row < endy; row++){
        clearRowBetween(beginx, endx, row);
    }
}


void ncursesWindow::clearRowBetween(int x1, int x2, int row){
    
    if(x1 < 0){
        x1 = 0;
    }
    
    if(x2 > m_length){
        x2 = m_length;
    }
    
    for(int y = x1; y < x2; y++){
        drawAt(y, row, " ");
    }
}


void ncursesWindow::clearColumnBetween(int y1, int y2, int column){
    
    if(y1 < 0){
        y1 = 0;
    }
    
    if(y2 > m_height){
        y1 = m_height;
    }
    
    for(int x = y1; x < y2; x++){
        drawAt(column, x, " ");
    }
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



