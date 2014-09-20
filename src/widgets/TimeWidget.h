//
//  TimeWidget.h
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 9/1/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//

#ifndef __warpdriveoverloaded__TimeWidget__
#define __warpdriveoverloaded__TimeWidget__


#include "widget.h"
#include "wintypes/window.h"


class GenericWindow;

class TimeWidget: public Widget {
    
public:
    
    TimeWidget(_SharedPtr<GenericWindow> parent, int xpos, int ypos) : Widget(parent, xpos, ypos){};
    
    void render();
    void refresh();
    void resize(int newx, int newy);
    void handleKeys(int input);
    
    void hide(){m_hidden = true;}
    void show(){m_hidden = false;}
    void toggleHidden(){m_hidden = !m_hidden;}
    
protected:
    
    bool m_hidden;
    
};
#endif /* defined(__warpdriveoverloaded__TimeWidget__) */
