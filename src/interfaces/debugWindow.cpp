//
//  debugWindow.cpp
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 8/29/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//

#include "debugWindow.h"
#include "wintypes/ncurseswindow.h"
#include "util/version.h"
#include <string>

DebugInterface::DebugInterface(_SharedPtr<Shell> owner) : Interface(owner){
    
}


void DebugInterface::init(){
    
    m_mainWindow = _SharedPtr<ncursesWindow>(new ncursesWindow(m_owner->getHeight(), m_owner->getWidth(), 0, 0)); // Initialize our root window
    

    m_mainWindow->hideBorder();
    m_mainWindow->refresh();

    m_mainWindow->setNormalColor(COLOR_GREEN, COLOR_BLACK);
    
    std::string welcome = "Welcome to Nostradamus OS";
    m_mainWindow->drawAt((int)(m_width - welcome.size())/2, 8, welcome);
    m_mainWindow->drawAt((int)(m_width - global_version_string.size())/2, 9, global_version_string);

    
    std::string pleasecontinue = "Press Tab to Continue";
    m_mainWindow->drawAt((int)(m_width - pleasecontinue.size()+1)/2, m_height-5, pleasecontinue, 0, 0, A_BLINK);

    m_mainWindow->refresh();
    m_mainWindow->render();

    m_initialized = true;
    
}


void DebugInterface::run(){
    
    //init_pair(1, COLOR_GREEN, COLOR_BLACK); // A default Background Color
    //wbkgd(m_mainWindow->get(), COLOR_PAIR(1)); // Set the background color accordingly
    //mvwprintw(m_mainWindow->get(), 8, (int)(m_width - welcome.size())/2, "%s", welcome.c_str());
    //mvwprintw(m_mainWindow->get(), 9, (int)(m_width - global_version_string.size())/2,"%s", global_version_string.c_str());
    std::string welcome = "Welcome to Nostradamus OS";
    m_mainWindow->drawAt((int)(m_width - global_version_string.size())/2, 9, global_version_string, 0, 0, A_BLINK);
    m_mainWindow->drawAt((int)(m_width - global_version_string.size())/2, 9, global_version_string);

    /*
    wattron(m_mainWindow->get(), A_BLINK);
    std::string pleasecontinue = "Press Tab to Continue";
    mvwprintw(m_mainWindow->get(), m_height-5, (int)(m_width - pleasecontinue.size()+1)/2,"%s", pleasecontinue.c_str());
    wattroff(m_mainWindow->get(), A_BLINK);
    wrefresh(m_mainWindow->get());
     */
    std::string pleasecontinue = "Press Tab to Continue";
    m_mainWindow->drawAt((int)(m_width - pleasecontinue.size()+1)/2, m_height-5, pleasecontinue, 0, 0, A_BLINK);
    
}



void DebugInterface::handleKeys(int input){
    
    
    
}