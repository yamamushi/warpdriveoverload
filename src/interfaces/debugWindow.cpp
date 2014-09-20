//
//  debugWindow.cpp
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 8/29/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//

#include "debugWindow.h"
#include "managers/ColorManager.h"
#include "util/version.h"
#include <string>

DebugInterface::DebugInterface(_SharedPtr<Shell> owner) : Interface(owner){
    
}


void DebugInterface::init(){
    
    m_mainWindow->hideBorder();
    //m_mainWindow->refresh();

    m_mainWindow->setNormalColor(COLOR_GREEN, COLOR_BLACK);
    
    std::string welcome = "The ASCII Project Rendering Framework";
    m_mainWindow->drawAt((int)(m_width - welcome.size())/2, 8, welcome);
    m_mainWindow->drawAt((int)(m_width - global_version_string.size())/2, 9, global_version_string);

    
    std::string pleasecontinue = "Press Tab to Continue";
    m_mainWindow->drawAt((int)(m_width - pleasecontinue.size()+1)/2, m_height-5, pleasecontinue, 0, 0, A_BLINK);

    m_mainWindow->refresh();
    m_mainWindow->render();

    m_initialized = true;
    
}


void DebugInterface::run(){
    
    std::string welcome = "The ASCII Project Rendering Framework";
    m_mainWindow->drawAt((int)(m_width - welcome.size())/2, 8, welcome);
    m_mainWindow->drawAt((int)(m_width - global_version_string.size())/2, 9, global_version_string);

    std::string pleasecontinue = "Press Tab to Continue";
    m_mainWindow->drawAt((int)(m_width - pleasecontinue.size()+1)/2, m_height-5, pleasecontinue, 0, 0, A_BLINK);
    
}



void DebugInterface::handleKeys(int input){
    
    
    
}