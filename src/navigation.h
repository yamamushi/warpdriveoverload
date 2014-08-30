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
    
};


#endif /* defined(__warpdriveoverloaded__navigation__) */
