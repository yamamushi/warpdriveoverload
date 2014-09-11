//
//  interface.cpp
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 8/29/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//

#include "interface.h"
#include <algorithm>

InterfaceHandler* InterfaceHandler::m_pInstance = NULL;


InterfaceHandler* InterfaceHandler::instance(){
    
    if (!m_pInstance){
        m_pInstance = new InterfaceHandler;
    }
    
    return m_pInstance;
    
}


InterfaceHandler::InterfaceHandler(){
    
    ;
    
}

void InterfaceHandler::addInterface(_SharedPtr<Interface> target){
    
    l_interfaceList.push_back(target);
    
}


void InterfaceHandler::removeInterface(_SharedPtr<Interface> target){
    
     std::vector<_SharedPtr<Interface>>::iterator it = std::find(l_interfaceList.begin(), l_interfaceList.end(), target);
     if (it != l_interfaceList.end()){
         l_interfaceList.erase(std::remove(l_interfaceList.begin(), l_interfaceList.end(), target), l_interfaceList.end());
     }
}




Interface::Interface(_SharedPtr<Shell> owner) : m_owner(owner){
    
    m_mainWindow = m_owner->createWindow();

    m_initialized = false;
    m_height = m_mainWindow->getY();
    m_width = m_mainWindow->getX();
    m_widgetManager = _SharedPtr<WidgetManager>(new WidgetManager(this));

}

void Interface::resizeConsole(int width, int height){
    
    m_width = width;
    m_height = height;
    
    resizeComponents();
    
}

GraphicsDriverManager * Interface::getGraphicsDriver(){

    return m_owner->getGraphicsDriver();

}


void Interface::queueCommand(_STD_FUNCTION(void()) target){
    
    l_functionList.push(target);
    
}


void Interface::run(){
    
    if(l_functionList.size() == 0){
        return; // No arguments to run
    }
    
    while(l_functionList.size() != 0){
        
        _STD_FUNCTION(void()) command = l_functionList.pop();

        command();
        
    }
    
}