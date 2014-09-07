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
#include "menu.h"
#include "window.h"
#include "widget.h"

#include "tr1_wrapper.h"

class DebugInterface : public Interface {
    
public:
    
    DebugInterface(_SharedPtr<Shell> owner);
    
    void init();
    void run();
    void handleKeys(int input);
    void draw(){};
    
protected:
    
    void resizeComponents(){}
    
private:
    
    _SharedPtr<GenericWindow> m_window;
    
};


#endif /* defined(__warpdriveoverloaded__debugWindow__) */
