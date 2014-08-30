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
#include "widget.h"
#include "graphchart.h"
#include "interface.h"

#include <string>
#include <ncurses.h>
#include <iostream>
#include <vector>

struct GraphChartPoint;

class Interface;

class Shell : public std::enable_shared_from_this<Shell>{
    
public:
    
    Shell(_SharedPtr<Nostradamus> parent) : m_parent(parent){m_running = false;}
    ~Shell(){shutdown();}
    
    bool running(){return m_running;}
    void boot();
    bool run();
    
    void loadInterfaces(_SharedPtr<Shell> parent);

    void refreshShell();
    
    void removeFromInterfaceList(_SharedPtr<Interface> target);
    void addToInterfaceList(_SharedPtr<Interface> target);
    
    _SharedPtr<Interface> getRootInterface(){return m_interfaceList.at(0);};

    void quit();


protected:
    
    friend class InterfaceHandler;
    friend class Interface;
    
    bool init();
    void populateInterfaces();
    
    void addToWindowList(_SharedPtr<ncursesWindow> target);
    void removeFromWindowList(_SharedPtr<ncursesWindow> target);
    
    _SharedPtr<Shell> getSharedPtr(){return shared_from_this();}

    void shutdown();
    void execute();
    
    void handleKeys(int input);
    
    void initMainWindow();
    _SharedPtr<ncursesWindow> getLastWindow(){return m_windows.back();}
    
    void createWindow(int ysize, int xsize);
    void close_win(_SharedPtr<ncursesWindow> target_window);
    
    void organizeInterfaces();
    
    bool checkForResize();
    
    _SharedPtr<Nostradamus> m_parent;
    
    bool m_running;
    
    int m_rows;
    int m_cols;
    
    _SharedPtr<ncursesWindow> m_mainWindow;
    _SharedPtr<Interface> m_topInterface;
    
    std::vector<_SharedPtr<ncursesWindow> > m_windows;

    void doNothing(){};
    void printDebug();
    
    std::vector<_SharedPtr<Interface> > m_interfaceList;
    
};


#endif /* defined(__warpdriveoverloaded__shell__) */
