#
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
#include "widget.h"
#include "ColorManager.h"

#include <string>

class ncursesMenu;
class Widget;

struct winBorder {
    
    char m_ls, m_rs, m_ts, m_bs, m_tl, m_tr, m_bl, m_br;

};

struct Pixel {
    
    int x, y;
    int attr;
    int fg;
    int bg;
    std::string s;
    
    Pixel(int px=0, int py=0, int attributes=0, int fgcolor=0, int bgcolor=0, std::string symbol=" ") : x(px), y(py), attr(attributes), fg(fgcolor), bg(bgcolor), s(symbol){};
    
};


class ncursesWindow : public std::enable_shared_from_this<ncursesWindow>{
    
public:
    ncursesWindow(int height, int length, int ypos, int xpos);
    
    WINDOW * get(){return m_window;}
    void close();
    
//    void addMenu(_SharedPtr<ncursesMenu> target){m_menuList.push_back(target);}
    void addWidget(_SharedPtr<Widget> target);
    void removeWidget(_SharedPtr<Widget> target);

    int getX(){return m_length;};
    int getY(){return m_height;};
    int getXpos(){return m_xpos;};
    int getYpos(){return m_ypos;};
    
    void clearLine(int line, int from=0){clearRow(line, from);}
    void clearRow(int row, int from=0);
    void clearColumn(int column, int from=0);
    
    void setborder(char ls, char rs, char ts, char bs, char tl, char tr, char bl, char br);
    _SharedPtr<winBorder> getBorder(){return m_border;}
    void drawBorder();
    
    void showBorder(){m_showBorder = true;}
    void hideBorder(){m_showBorder = false;}
    void toggleBorder(){m_showBorder = !m_showBorder;}
    
    void render();
    void refresh();
    
    void handleKeys(int input);
    void clearScreen();
    
    void drawAt(int x, int y, std::string output);
    void drawAt(int x, int y, std::string output, int fg, int bg=0);
    void drawAt(int x, int y, char c);
    void drawAt(int x, int y, char c, int fg, int bg=0);
    
    void putPixel(_SharedPtr<Pixel> point);
    
    void move(int newX, int newY);
    void resize(int height, int length, int ypos, int xpos);
    
    void setBGColor(int color){m_bgColor = color;}
    int getBGColor(){return m_bgColor;}
    
    void setNormalColor(int fg, int bg);
    int getNormalColor(){return m_normalColor;}
    
    void setFGColor(int color){m_fgColor = color;}
    int getFGColor(){return m_fgColor;}
    
    void setSelectedColor(int fg, int bg=0);
    int getSelectedColor(){return m_selectedColor;}
    
    void setCursorColor(int fg, int bg=0);
    int getCursorColor(){return m_cursorColor;}
    
    void setBorderColor(int fg, int bg=0);
    int getBorderColor(){return m_borderColor;}
    
    
    short checkColorPair(short wanted_fore, int wanted_back);
    
private:
    
    int m_height, m_length, m_ypos, m_xpos;
    int m_colorPaircount;

    
    WINDOW *m_window;
    
    std::vector<_SharedPtr<ncursesWindow>> m_windowList;
    std::vector<_SharedPtr<Widget>> m_widgetList;
    
    bool m_showBorder;
    
    int m_bgColor;
    int m_fgColor;
    int m_selectedColor;
    int m_cursorColor;
    int m_normalColor;
    int m_borderColor;

    _SharedPtr<winBorder> m_border;
    int m_color;
};


#endif /* defined(__warpdriveoverloaded__window__) */
