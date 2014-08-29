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
#include "window.h"
#include "ncursespanel.h"

#include <string>
#include <ncurses.h>
#include <panel.h>
#include <iostream>
#include <vector>
#include <panel.h>

class ncursesPanel;

class Shell {
    
public:
    Shell(_SharedPtr<Nostradamus> parent) : m_parent(parent){m_running = false;}
    ~Shell(){shutdown();}
    
    bool running(){return m_running;}
    void boot();
    
    
    void panelRefresh(){update_panels();}
    
private:
    
    
    bool init();
    void shutdown();
    void quit();
    
    void createWindow(int ysize, int xsize);
    
    void addToPanelList(_SharedPtr<ncursesWindow> targetWindow);
    void close_win(_SharedPtr<ncursesWindow> target_window);
    
    
    void SetStdinEcho(bool enable = true);
    _SharedPtr<Nostradamus> m_parent;
    
    bool m_running;
    
    int m_rows;
    int m_cols;
    
    _SharedPtr<ncursesWindow> m_mainWindow;
    
    std::vector<_SharedPtr<ncursesWindow> > m_windows;
    std::vector<_SharedPtr<ncursesPanel> > m_panels;

    void doNothing(){};
    void printDebug();
};


#endif /* defined(__warpdriveoverloaded__shell__) */
