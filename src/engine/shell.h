#pragma once
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

#include "managers/GraphicsDriverManager.h"

#include "engine/game_engine.h"
#include "tr1/tr1_wrapper.h"
#include "wintypes/window.h"

#include "widgets/widget.h"
#include "widgets/graphchart.h"
#include "interfaces/interface.h"

#include <string>
#include <vector>

#include "managers/ColorManager.h"
#include "util/Clock.h"







class GraphicsDriverManager;

struct GraphChartPoint;

class Interface;

class Shell : public std::enable_shared_from_this<Shell>{
    
public:
    
    Shell(_SharedPtr<Nostradamus> parent) : m_parent(parent){m_running = false;}
    ~Shell(){shutdown();}
    
    bool running(){return m_running;}
    void boot();
    bool run();
    
    int getfps();
    void setmaxfps(int fps);
    
    int getHeight(){return m_rows;}
    int getWidth(){return m_cols;}
    
    void loadInterfaces(_SharedPtr<Shell> parent);

    void refreshShell();
    
    void removeFromInterfaceList(_SharedPtr<Interface> target);
    void addToInterfaceList(_SharedPtr<Interface> target);
    
    _SharedPtr<Interface> getRootInterface(){return m_interfaceList.at(0);};

    GraphicsDriverManager *getGraphicsDriver(){return m_graphicsManager;}

    void quit();

    void doNothing(){};
    void printDebug();
    
    _SharedPtr<GenericWindow> createWindow();

    // For Linemode and grabbing key input
    void enableRaw();
    void disableRaw();
    

protected:
    
    friend class InterfaceHandler;
    friend class Interface;
    
    bool init();
    void populateInterfaces();
    
    void addToWindowList(_SharedPtr<GenericWindow> target);
    void removeFromWindowList(_SharedPtr<GenericWindow> target);
    
    _SharedPtr<Shell> getSharedPtr(){return shared_from_this();}

    void shutdown();
    void execute();
    
    void handleKeys(int input);

    
    void initMainWindow();
    _SharedPtr<GenericWindow> getLastWindow(){return m_windows.back();}
    
    void createWindow(int ysize, int xsize);
    void close_win(_SharedPtr<GenericWindow> target_window);
    
    void organizeInterfaces();
    
    bool checkForResize();

    std::vector<_SharedPtr<Interface> > m_interfaceList;
    
private:
    
    _SharedPtr<Nostradamus> m_parent;
    
    GraphicsDriverManager *m_graphicsManager;
    
    int m_maxfps;
    
    _SharedPtr<GenericWindow> m_mainWindow;
    _SharedPtr<Interface> m_topInterface;
    
    std::vector<_SharedPtr<GenericWindow> > m_windows;
    
    bool m_running;
    
    int m_rows;
    int m_cols;
    
    // Start Up Object
    
    
};


#endif /* defined(__warpdriveoverloaded__shell__) */
