//
//  WidgetManager.cpp
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 9/5/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//

#include "WidgetManager.h"


WidgetManager::WidgetManager(Interface *owner) : m_owner(owner) {
    
    
    m_mainWindow = m_owner->getWindow();
    
    
}


void WidgetManager::handleKeys(int input){
    
    
    
}




void WidgetManager::addWidget(_SharedPtr<Widget> target){
    
    m_widgetList.push_back(target);
    
    m_mainWindow->addWidget(target);


}


void WidgetManager::selectWidget(_SharedPtr<Widget> target){
    
    m_activeWidget = target;
    
}