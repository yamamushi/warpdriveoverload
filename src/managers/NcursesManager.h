//
//  NcursesManager.h
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 9/7/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//

#ifndef __warpdriveoverloaded__NcursesManager__
#define __warpdriveoverloaded__NcursesManager__

#include "GraphicsDriverManager.h"

#include "wintypes/ncurseswindow.h"
#include <ncurses.h>

class NcursesManager : public GraphicsDriverManager {
    
public:
    
    bool start();
    
    int getWidth();
    int getHeight();
    int getfps();
    void setmaxfps(int fps);
    
    _SharedPtr<GenericWindow> getNewWindow();

    int getInput();
    
    void startRawInputFeed();
    void stopRawInputFeed();
    
    void shutdown();
    
    
protected:
    
    friend class Shell;
    

    
private:
    
    
};


#endif /* defined(__warpdriveoverloaded__NcursesManager__) */
