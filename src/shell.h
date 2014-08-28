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



class Shell {
    
public:
    Shell(_SharedPtr<Nostradamus> parent) : m_parent(parent){}
    ~Shell(){}
    
    
private:
    
    void SetStdinEcho(bool enable = true);
    _SharedPtr<Nostradamus> m_parent;
};


#endif /* defined(__warpdriveoverloaded__shell__) */
