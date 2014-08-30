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

class ncursesMenu;

struct winBorder {
    
    char m_ls, m_rs, m_ts, m_bs, m_tl, m_tr, m_bl, m_br;

};

class ncursesWindow : public std::enable_shared_from_this<ncursesWindow>{
    
public:
    ncursesWindow(int height, int length, int ypos, int xpos);
    
    WINDOW * get(){return m_window;}
    void close();
    
    void addMenu(_SharedPtr<ncursesMenu> target){m_menuList.push_back(target);}
    void addWidget(_SharedPtr<Widget> target);
    void removeWidget(_SharedPtr<Widget> target);

    int getX(){return m_length;};
    int getY(){return m_height;};
    int getXpos(){return m_xpos;};
    int getYpos(){return m_ypos;};
    
    
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
    
    void closeAllMenus();
    
    void move(int newX, int newY);
    void resize(int height, int length, int ypos, int xpos);
    
    void setBGColor(int color){m_bgColor = color;}
    int getBGColor(){return m_bgColor;}
    
    void setNormalColor(int color){m_normalColor = COLOR_PAIR(color);}
    int getNormalColor(){return m_normalColor;}
    
    void setFGColor(int color){m_fgColor = COLOR_PAIR(color);}
    int getFGColor(){return m_fgColor;}
    
    void setSelectedColor(int color){m_selectedColor = COLOR_PAIR(color);}
    int getSelectedColor(){return m_selectedColor;}
    
    void setCursorColor(int color){m_cursorColor = COLOR_PAIR(color);}
    int getCursorColor(){return m_cursorColor;}
    
    void setBorderColor(int color){m_borderColor = COLOR_PAIR(color);}
    int getBorderColor(){return m_borderColor;}

private:
    
    int m_height, m_length, m_ypos, m_xpos;
    
    WINDOW *m_window;
    
    std::vector<_SharedPtr<ncursesMenu>> m_menuList;
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
