//
//  debugWindow.h
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 8/29/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//

#ifndef __warpdriveoverloaded__debugWindow__
#define __warpdriveoverloaded__debugWindow__

#include "interface.h"
#include "ncursespanel.h"
#include "menu.h"
#include "window.h"
#include "widget.h"

#include "tr1_wrapper.h"

class DebugInterface : public Interface {
    
public:
    
    DebugInterface(_SharedPtr<Shell> owner);
    
    void init();
    void run();
    void handleKeys(int input){};
    
private:
    
    _SharedPtr<ncursesWindow> m_window;
    
};


#endif /* defined(__warpdriveoverloaded__debugWindow__) */