#pragma once
//
//  window.h
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 8/28/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//
//
//  A generic display template for rendering.
//
//

#ifndef __warpdriveoverloaded__window__
#define __warpdriveoverloaded__window__

#include <vector>
#include <string>

#include "tr1/tr1_wrapper.h"
#include "widgets/widget.h"


class Widget;

struct winBorder {
    
    char m_ls, m_rs, m_ts, m_bs, m_tl, m_tr, m_bl, m_br;

};

struct Pixel {
    
    int x, y;
    int attr;
    int fg;
    int bg;
    char c;
    
    Pixel(int px=0, int py=0, int attributes=0, int fgcolor=0, int bgcolor=0, char symbol=' ') : x(px), y(py), attr(attributes), fg(fgcolor), bg(bgcolor), c(symbol){};
    
};


class GenericWindow : public std::enable_shared_from_this<GenericWindow>{
    
public:
   
    GenericWindow(int height, int length, int ypos, int xpos);
    
    
    // Generic Window information
    int getX(){return m_length;};
    int getY(){return m_height;};
    int getXpos(){return m_xpos;};
    int getYpos(){return m_ypos;};
    
    
    // Widget Management
    void addWidget(_SharedPtr<Widget> target);
    void removeWidget(_SharedPtr<Widget> target);


    // Screen Drawing
    virtual void render(){};
    virtual void refresh(){};
    virtual void clearScreen(){};
    virtual void close(){};

    virtual void clearArea(int x1, int y1, int x2, int y2){};
    virtual void clearRowBetween(int x1, int x2, int row){};
    virtual void clearColumnBetween(int y1, int y2, int column){};

    void clearLineFrom(int line, int from=0){clearRow(line, from);}
    virtual void clearRow(int row, int from=0){};
    virtual void clearColumn(int column, int from=0){};
    
    virtual void drawAt(int x, int y, std::string output){};
    virtual void drawAt(int x, int y, std::string output, int fg, int bg=0, int attr=0){};
    virtual void drawAt(int x, int y, char c){};
    virtual void drawAt(int x, int y, char c, int fg, int bg=0, int attr=0){};
    
    virtual void putPixel(_SharedPtr<Pixel> point){};
    virtual void move(int newX, int newY){m_xpos = newX; m_ypos = newY;}
    // Resize is Virtual because some drivers may handle this differently .
    virtual void resize(int height, int length, int ypos=0, int xpos=0){};
    virtual void drawLine(int x1, int y1, int x2, int y2, std::string symbol, int fg=0, int bg=0, int attr=0){};
    
    
    
    // Border Management
    void showBorder(){m_showBorder = true;}
    void hideBorder(){m_showBorder = false;}
    void toggleBorder(){m_showBorder = !m_showBorder;}
    void setborder(char ls, char rs, char ts, char bs, char tl, char tr, char bl, char br);
    virtual void drawBorder(){};
    _SharedPtr<winBorder> getBorder(){return m_border;}


    // Other Needed Functions
    virtual void handleKeys(int input){};
    
    
    // Color Management
    
    
    
    virtual void setNormalColor(int fg, int bg){};
    int getNormalColor(){return m_normalColor;}
    
    void setFGColor(int color){m_fgColor = color;}
    int getFGColor(){return m_fgColor;}
    
    void setBGColor(int color){m_bgColor = color;}
    int getBGColor(){return m_bgColor;}
    
    
    virtual void setSelectedColor(int fg, int bg=0){};
    int getSelectedColor(){return m_selectedColor;}
    
    void setSelectedColorfg(int fg){ m_selectedColorfg = fg;};
    int getSelectedColorfg(){return m_selectedColorfg;}
    
    void setSelectedColorbg(int bg){ m_selectedColorbg = bg;};
    int getSelectedColorbg(){return m_selectedColorbg;}
    
    
    virtual void setCursorColor(int fg, int bg=0){};
    int getCursorColor(){return m_cursorColor;}
    
    void setCursorColorfg(int fg){ m_cursorColorfg = fg;};
    int getCursorColorfg(){return m_cursorColorfg;}
    
    void setCursorColorbg(int bg){ m_cursorColorbg = bg;};
    int getCursorColorbg(){return m_cursorColorbg;}
    
    
    virtual void setBorderColor(int fg, int bg=0){};
    int getBorderColor(){return m_borderColor;}
    
    void setBorderColorfg(int fg){ m_borderColorfg = fg;};
    int getBorderColorfg(){return m_borderColorfg;}
    
    void setBorderColorbg(int bg){ m_borderColorbg = bg;};
    int getBorderColorbg(){return m_borderColorbg;}
    
protected:

    // Data only our child classes should ever touch
    int m_height, m_length, m_ypos, m_xpos;
    
    std::vector<_SharedPtr<GenericWindow>> m_windowList;
    std::vector<_SharedPtr<Widget>> m_widgetList;
    
    
    // Border Objects
    _SharedPtr<winBorder> m_border;
    bool m_showBorder;

    
    // Colors
    int m_selectedColor;
    int m_selectedColorfg;
    int m_selectedColorbg;
    
    int m_cursorColor;
    int m_cursorColorfg;
    int m_cursorColorbg;
    
    int m_normalColor;
    int m_bgColor;
    int m_fgColor;
    
    int m_borderColor;
    int m_borderColorfg;
    int m_borderColorbg;

};


#endif /* defined(__warpdriveoverloaded__window__) */
