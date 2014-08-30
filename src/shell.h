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
#include "widget.h"
#include "graphchart.h"
#include "interface.h"

#include <string>
#include <ncurses.h>
#include <panel.h>
#include <iostream>
#include <vector>
#include <panel.h>

struct GraphChartPoint;

class ncursesPanel;
class Interface;

class Shell {
    
public:
    Shell(_SharedPtr<Nostradamus> parent) : m_parent(parent){m_running = false;}
    ~Shell(){shutdown();}
    
    bool running(){return m_running;}
    void boot();
    
    void refreshShell();

    void addToWindowList(_SharedPtr<ncursesWindow> target);
    void removeFromWindowList(_SharedPtr<ncursesWindow> target);
    
    void removeFromPanelList(_SharedPtr<ncursesPanel> target);
    void addToPanelList(_SharedPtr<ncursesWindow> targetWindow);
    
    _SharedPtr<ncursesPanel> getRootPanel(){return m_panels.at(0);};

    
private:
    
    friend class InterfaceHandler;
    friend class Interface;
    
    bool init();
    void populatePanels();
    
    void loadInterfaces();
    void shutdown();
    
    void run();
    void handleKeys(int input);
    
    void quit();
    
    void createWindow(int ysize, int xsize);
    void close_win(_SharedPtr<ncursesWindow> target_window);
    
    void organizePanels();
    
    bool checkForResize();
    
    _SharedPtr<Nostradamus> m_parent;
    
    bool m_running;
    
    int m_rows;
    int m_cols;
    
    _SharedPtr<ncursesWindow> m_mainWindow;
    _SharedPtr<ncursesPanel> m_topPanel;
    
    std::vector<_SharedPtr<ncursesWindow> > m_windows;
    std::vector<_SharedPtr<ncursesPanel> > m_panels;

    void doNothing(){};
    void printDebug();
    
    _SharedPtr<Widget> graphController;
    _SharedPtr<Interface> m_interfaceList;
    
};


#endif /* defined(__warpdriveoverloaded__shell__) */
