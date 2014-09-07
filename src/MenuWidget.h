//
//  MenuWidget.h
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 9/5/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//

#ifndef __warpdriveoverloaded__MenuWidget__
#define __warpdriveoverloaded__MenuWidget__

#include "tr1_wrapper.h"
#include "tr1_threading.h"
#include "widget.h"

class GenericWindow;

class MenuWidget : public Widget {
    
public:
    
    MenuWidget(_SharedPtr<GenericWindow> parent, int xpos, int ypos) : Widget(parent, xpos, ypos){};
    
    void render(){};
    void refresh(){};
    void resize(int newx, int newy){};
    void handleKeys(int input){};
    
    void hide(){m_hidden = true;}
    void show(){m_hidden = false;}
    void toggleHidden(){m_hidden = !m_hidden;}
    
    void open();
    void close();
    
    void move(int x, int y){};
    
    
    void addMenuItem(std::string name, _STD_FUNCTION(void()) command);
    void addSubMenu( std::string name, _SharedPtr<MenuWidget> submenu);
    
    void openSubMenu(std::string name);
    
    void selectNext();
    void selectPrev();
    
    void highlightItem(std::string name);
    void highlightItem(int itemID);
    
    
    
protected:
    
    bool m_hidden;
    
    std::vector<std::pair<std::string, _STD_FUNCTION(void())> > m_menuList;

    
};


#endif /* defined(__warpdriveoverloaded__MenuWidget__) */
