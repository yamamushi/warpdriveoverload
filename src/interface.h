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

#include <ncurses.h>
#include <vector>

class Interface;
class ncursesInterface;
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
    
    _SharedPtr<ncursesWindow> getWindow(){return m_mainWindow;}
    
    virtual void run();
    virtual void init(){};
    virtual void handleKeys(int input){};
    bool initialized(){return m_initialized;}
    
    _SharedPtr<Interface> getChild(){return m_child;}
    _SharedPtr<Interface>  getNext(){return m_next;}
    _SharedPtr<Interface>  getPrevl(){return m_prev;}
    
    void setName(std::string name){m_name = name;}
    std::string getName(){return m_name;}
    
protected:
    
    friend class Shell;
    
    MsgQueue<_STD_FUNCTION(void())> l_functionList;
    _SharedPtr<Shell> m_owner;
    
    _SharedPtr<ncursesInterface> m_Interface;
    
    std::vector<_SharedPtr<Widget> > m_widgetList;
    
    std::vector<_SharedPtr<ncursesWindow> > m_windowList;
    _SharedPtr<ncursesWindow> m_mainWindow;
    
    void addToHandler(){InterfaceHandler::instance()->addInterface(shared_from_this());}
    
    bool m_initialized;
    int m_sizeX;
    int m_sizeY;
    
    void addNext(_SharedPtr<Interface>  nextInterface){m_next = nextInterface;}
    void addPrev(_SharedPtr<Interface>  prevInterface){m_prev = prevInterface;}
    
    _SharedPtr<Interface> m_child;
    _SharedPtr<Interface> m_prev;
    _SharedPtr<Interface> m_next;
    
    
    static int ID;
    int m_ID;
    
    std::string m_name;

};

#endif





















