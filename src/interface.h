//
//  interface.h
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 8/29/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//
/*
 
 Basically we want to dump our interface files here.
 
 
 
 */

#ifndef warpdriveoverloaded_interface_h
#define warpdriveoverloaded_interface_h


#include "messagequeue.h"
#include "tr1_threading.h"
#include "tr1_wrapper.h"
#include "shell.h"
#include "window.h"
#include "panel.h"

#include <ncurses.h>
#include <vector>

class Interface;
class ncursesPanel;
class ncursesWindow;
class Widget;
class Shell;

class InterfaceHandler {
    
public:

    static InterfaceHandler* instance();

    void run(){};
    
    void addInterface(_SharedPtr<Interface> target);
    void removeInterface(_SharedPtr<Interface> target);
    

private:
    
    InterfaceHandler();
    
    InterfaceHandler(InterfaceHandler const&);
    InterfaceHandler& operator=(InterfaceHandler const&);
    static InterfaceHandler* m_pInstance;
    
    std::vector<_SharedPtr<Interface> > l_interfaceList;
    
};



class Interface : public std::enable_shared_from_this<Interface>{
    
public:

    Interface(_SharedPtr<Shell> owner);
    ~Interface(){};
    
    void queueCommand(_STD_FUNCTION(void()) target);
    //void unqueueCommand(_STD_FUNCTION(void()) target);
    
    _SharedPtr<ncursesPanel> getPanel(){return m_panel;}
    
    virtual void run();
    virtual void init(){};
    virtual void handleKeys(int input){};
    bool initialized(){return m_initialized;}
    
    
protected:
    
    MsgQueue<_STD_FUNCTION(void())> l_functionList;
    _SharedPtr<Shell> m_owner;
    
    _SharedPtr<ncursesPanel> m_panel;
    
    std::vector<_SharedPtr<Widget> > m_widgetList;
    
    std::vector<_SharedPtr<ncursesWindow> > m_windowList;
    _SharedPtr<ncursesWindow> m_mainWindow;
    
    void addToHandler(){InterfaceHandler::instance()->addInterface(shared_from_this());}
    
    bool m_initialized;
    int m_sizeX;
    int m_sizeY;
    
};

#endif
