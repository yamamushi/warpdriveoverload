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

#include <vector>

class Interface;
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
    
    Interface(_SharedPtr<Shell> owner) : m_owner(owner){InterfaceHandler::instance()->addInterface(shared_from_this());};
    ~Interface(){InterfaceHandler::instance()->removeInterface(shared_from_this());};
    
    void addToInterface(_STD_FUNCTION(void()) target);
    void removeFromInterface(_STD_FUNCTION(void()) target);
    
    void run();
    
protected:
    
    MsgQueue<_STD_FUNCTION(void())> l_functionList;
    _SharedPtr<Shell> m_owner;
    
};

#endif
