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
    
}


void DebugInterface::init(){
    
    m_mainWindow->hideBorder();
    m_mainWindow->refresh();
    m_mainWindow->render();
    
    init_pair(1, COLOR_GREEN, COLOR_BLACK); // A default Background Color
    wbkgd(m_mainWindow->get(), COLOR_PAIR(1)); // Set the background color accordingly
    std::string welcome = "Welcome to Nostradamus OS";
    
    mvwprintw(m_mainWindow->get(), 8, (int)(m_width - welcome.size())/2, "%s", welcome.c_str());
    mvwprintw(m_mainWindow->get(), 9, (int)(m_width - global_version_string.size())/2,"%s", global_version_string.c_str());
    
    wattron(m_mainWindow->get(), A_BLINK);
    std::string pleasecontinue = "Press Tab to Continue";
    mvwprintw(m_mainWindow->get(), m_height-5, (int)(m_width - pleasecontinue.size()+1)/2,"%s", pleasecontinue.c_str());
    wattroff(m_mainWindow->get(), A_BLINK);
    
    wrefresh(m_mainWindow->get());
    
    m_initialized = true;
    
}


void DebugInterface::run(){
    
    init_pair(1, COLOR_GREEN, COLOR_BLACK); // A default Background Color
    wbkgd(m_mainWindow->get(), COLOR_PAIR(1)); // Set the background color accordingly
    std::string welcome = "Welcome to Nostradamus OS";
    
    mvwprintw(m_mainWindow->get(), 8, (int)(m_width - welcome.size())/2, "%s", welcome.c_str());
    mvwprintw(m_mainWindow->get(), 9, (int)(m_width - global_version_string.size())/2,"%s", global_version_string.c_str());
    
    wattron(m_mainWindow->get(), A_BLINK);
    std::string pleasecontinue = "Press Tab to Continue";
    mvwprintw(m_mainWindow->get(), m_height-5, (int)(m_width - pleasecontinue.size()+1)/2,"%s", pleasecontinue.c_str());
    wattroff(m_mainWindow->get(), A_BLINK);
    
    wrefresh(m_mainWindow->get());
    
}



void DebugInterface::handleKeys(int input){
    
    
    
}