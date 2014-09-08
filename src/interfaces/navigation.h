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
#include "widgets/menu.h"
#include "wintypes/window.h"

#include "widgets/widget.h"
#include "widgets/connectionwidget.h"
#include "widgets/MenuWidget.h"

#include <vector>

class NavigationInterface : public Interface {
    
public:
    
    NavigationInterface(_SharedPtr<Shell> owner) : Interface(owner){};
    
    void init();
    void run();
    void handleKeys(int input);
    void draw(){};
    
protected:
    
    void resizeComponents(){};
    
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
    
    void getInput();
    
    std::string testString;
    
    void setTargetCenter(int x, int y);
    void randomizeCenter();
    int m_targetcenterX;
    int m_targetcenterY;
    int m_randomCenterX;
    int m_randomCenterY;
    
};


#endif /* defined(__warpdriveoverloaded__navigation__) */
