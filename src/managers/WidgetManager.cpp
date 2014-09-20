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
    m_activeWidgetID = -1;
    m_activeWidgetIndex = -1;

}


void WidgetManager::handleKeys(int input){
    
}




void WidgetManager::addWidget(_SharedPtr<Widget> target){
    
    m_widgetList.push_back(target);
    
    //m_mainWindow->addWidget(target);

    m_activeWidgetID = target->getID();

    //m_activeWidgetIndex = m_widgetList.size() - 1;
}


void WidgetManager::selectWidget(_SharedPtr<Widget> target){
    
    m_activeWidget = target;
    
}

_SharedPtr<Widget> WidgetManager::getWidgetForID(int ID) {

    for(int x = 0; x < m_widgetList.size(); x++){

        if(m_widgetList.at(x)->getID() == ID )
            m_activeWidgetID = ID;
            m_activeWidgetIndex = x;
            return m_widgetList.at(x);
    }

    return nullptr;
}

_SharedPtr<Widget> WidgetManager::getPrevWidget() {

    if(m_activeWidgetIndex == -1){
        return nullptr;
    }

    if(m_widgetList.size() == 1){
        m_activeWidgetIndex = 0;
        return m_widgetList.at(m_activeWidgetIndex);
    }

    if(m_activeWidgetIndex == 0){
        m_activeWidgetIndex = (m_widgetList.size()-1);
        return m_widgetList.at(m_activeWidgetIndex);
    }

    --m_activeWidgetIndex;

    return m_widgetList.at(m_activeWidgetIndex);
    

}

_SharedPtr<Widget> WidgetManager::getNextWidget() {

    if(m_activeWidgetIndex == -1){
        return nullptr;
    }

    if(m_widgetList.size() == 1){
        m_activeWidgetIndex = 0;
        return m_widgetList.at(m_activeWidgetIndex);
    }

    if(m_activeWidgetIndex == m_widgetList.size()-1){
        m_activeWidgetIndex = 0;
        return m_widgetList.at(m_activeWidgetIndex);
    }

    ++m_activeWidgetIndex;

    return m_widgetList.at(m_activeWidgetIndex);

}

_SharedPtr<Widget> WidgetManager::getActiveWidget() {

    return getWidgetForID(m_activeWidgetID);
}


void WidgetManager::render(){

    for(int x = 0; x < m_widgetList.size(); x++) {
        m_widgetList.at(x)->render();
    }

}