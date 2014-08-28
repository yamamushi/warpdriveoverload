//
//  shell.h
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 8/28/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//

#ifndef __warpdriveoverloaded__shell__
#define __warpdriveoverloaded__shell__

#ifdef WIN32
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
#endif


#include "term_control.h"
#include "game_engine.h"
#include "tr1_wrapper.h"

#include <string>
#include <ncurses.h>
#include <iostream>


class Shell {
    
public:
    Shell(_SharedPtr<Nostradamus> parent) : m_parent(parent){m_running = false;}
    ~Shell(){shutdown();}
    
    bool running(){return m_running;}
    
    void boot();
    
    
    
private:
    
    
    bool init();
    void shutdown();
    
    
    void SetStdinEcho(bool enable = true);
    _SharedPtr<Nostradamus> m_parent;
    
    bool m_running;
    
};


#endif /* defined(__warpdriveoverloaded__shell__) */
