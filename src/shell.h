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




class Shell {
    
public:
    Shell(){}
    ~Shell(){}
    
    
private:
    
    void SetStdinEcho(bool enable = true);
    
};


#endif /* defined(__warpdriveoverloaded__shell__) */
