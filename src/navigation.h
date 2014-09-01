//
//  navigation.h
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 8/29/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//

#ifndef __warpdriveoverloaded__navigation__
#define __warpdriveoverloaded__navigation__

#include "interface.h"
#include "menu.h"
#include "window.h"
#include "widget.h"
#include "connectionwidget.h"

#include <ncurses.h>
#include <vector>

class NavigationInterface : public Interface {
    
public:
    
    NavigationInterface(_SharedPtr<Shell> owner) : Interface(owner){};
    
    void init();
    void run();
    void handleKeys(int input);
    
private:
    
    //std::vector<_SharedPtr<Widget> > m_widgetList;
    void randDirection();
    int lotteryLimit;
    
    _SharedPtr<GraphChart> graphController;
    _SharedPtr<ConnectionWidget> connectionStatus;
    _SharedPtr<ncursesMenu> menuNavigation;
    
    int m_graphX;
    int m_graphY;
    
    void drawAt(int x=-1, int y=-1);
    void failedAt(int x=-1, int y=-1){};
    
    void doNothing(){};
    
};


#endif /* defined(__warpdriveoverloaded__navigation__) */
