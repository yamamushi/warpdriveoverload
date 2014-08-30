//
//  debugWindow.cpp
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 8/29/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//

#include "debugWindow.h"
#include "version.h"
#include <string>

DebugInterface::DebugInterface(_SharedPtr<Shell> owner) : Interface(owner){
    
    m_panel = owner->getRootPanel();
    
}


void DebugInterface::init(){
    
    m_mainWindow = m_panel->getChild();
    m_sizeY = m_mainWindow->getY();
    m_sizeX = m_mainWindow->getX();
    
    init_pair(1, COLOR_GREEN, COLOR_BLACK); // A default Background Color
    wbkgd(m_mainWindow->get(), COLOR_PAIR(1)); // Set the background color accordingly
    
    std::string welcome = "Welcome to Nostradamus OS";
    
    attroff(A_BOLD);
    
    mvwprintw(m_mainWindow->get(), (m_sizeY/2)-1, (m_sizeX - welcome.size())/2, "%s", welcome.c_str());
    mvwprintw(m_mainWindow->get(), m_sizeY/2,(m_sizeX - global_version_string.size())/2,"%s", global_version_string.c_str());
    
    wattron(m_mainWindow->get(), A_BLINK);
    
    std::string pleasecontinue = "Press any key to Continue";
    
    mvwprintw(m_mainWindow->get(), m_sizeY-5,(m_sizeX - pleasecontinue.size()+1)/2,"%s", pleasecontinue.c_str());
    
    wattroff(m_mainWindow->get(), A_BLINK);
    
    wrefresh(m_mainWindow->get());
    
    refresh();
    getch();
    
    m_owner->addToInterfaceList(shared_from_this());
    
}


void DebugInterface::run(){
    
    
}