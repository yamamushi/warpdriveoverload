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
#include <utility>
#include "tr1_wrapper.h"
#include "tr1_threading.h"

struct winBorder;

class ncursesWindow;

enum class menuAlignment {
    LEFT,
    CENTER,
    RIGHT
};

class ncursesMenu {
    
public:
    ncursesMenu(std::vector<std::pair<std::string, _STD_FUNCTION(void())> > menuList, std::string m_name, _SharedPtr<ncursesWindow> parent = nullptr, bool horizontal = false);
    
    void setParent(_SharedPtr<ncursesWindow> target);
    _SharedPtr<ncursesWindow> getParent(){return m_parent;}
    
    
    void move(int ypos, int xpos);
    void render();
    
    void selectNext();
    void selectPrev();
    void selectNone();
    void showBorder(bool show);
    void highlightTitle(bool toggle = true){m_highlightTitle = toggle;}
    void showTitle(bool toggle = true){m_showTitle = toggle;}
    
    void setBGColor(int color){m_bgColor = color;}
    void setNormalColor(int color){m_normalColor = COLOR_PAIR(color);}
    void setFGColor(int color){m_fgColor = COLOR_PAIR(color);}
    void setSelectedColor(int color){m_selectedColor = COLOR_PAIR(color);}
    void setCursorColor(int color){m_cursorColor = COLOR_PAIR(color);}
    void setBorderColor(int color){m_borderColor = COLOR_PAIR(color);}
    
    void addSubMenu(_SharedPtr<ncursesMenu> item, int keyID);
    
    void toggleItem(int itemID);
    int getCurrentItem();
    
    void setHorizontal(bool option);
    void setborder(char ls, char rs, char ts, char bs, char tl, char tr, char bl, char br);
    void setAlignment(menuAlignment align = menuAlignment::LEFT);
    
    void toggleHide(){m_hidden = !m_hidden; m_selected = 0; m_subMenuControl = 0;}
    void hide(){m_hidden = true; m_selected = 0; m_subMenuControl = 0;}
    void show(){m_hidden = false;}
    bool getHidden(){return m_hidden;}
    void setSubMenuStatus(bool status){m_isSubMenu = status;}
    bool checkIfSubMenu(){return m_isSubMenu;}
    
    void resize();
    void closeSubMenu();
    void toggleSubMenu();
    
    void execute();
    
    void handleKeys(int input);
    
    void close();
    
    
private:
    
    _SharedPtr<ncursesWindow> m_parent;
    bool m_hidden;
    bool m_horizontal;
    std::vector<std::pair<std::string, _STD_FUNCTION(void())> > m_menuList;
    std::vector<std::pair<_SharedPtr<ncursesMenu>, int> > m_subMenuList;
    
    int m_xpos;
    int m_ypos;
    
    std::string m_name;
    
    void drawborder();
    int m_selected;
    std::vector<int> m_selectedList;
    bool m_showBorder;
    bool m_showTitle;
    bool m_highlightTitle;
    
    int m_menuSize;
    int m_width;
    int m_height;
    int m_bgColor;
    int m_fgColor;
    int m_selectedColor;
    int m_cursorColor;
    int m_normalColor;
    int m_borderColor;
    bool m_isSubMenu;

    
    bool m_subMenuOpen;
    int m_subMenuControl;
    
    menuAlignment m_alignment;
    
    
    _SharedPtr<winBorder> m_border;
};
#endif /* defined(__warpdriveoverloaded__menu__) */
