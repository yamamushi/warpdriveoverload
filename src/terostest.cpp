//
//  terostest.cpp
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 9/1/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//

#include "terostest.h"


void TerosTestInterface::init(){
    
    m_mainWindow->clearScreen();
    
    
    m_graphController = _SharedPtr<GraphChart>(new GraphChart(m_mainWindow, 0, 0));
    m_mainWindow->addWidget(m_graphController);
    
    
    m_terosScreen = _SharedPtr<TerosScreen>(new TerosScreen(m_mainWindow, 0, 0, m_graphController));
    m_mainWindow->addWidget(m_terosScreen);
    
    _SharedPtr<TerosWindow> l_testWindow  =  _SharedPtr<TerosWindow>(new TerosWindow( m_terosScreen, m_terosScreen->getwidth(), m_terosScreen->getheight(), 2, 2));
    
    m_terosScreen->addlayer(l_testWindow);
    m_mainWindow->drawAt(3, 3, "Testing");
//    m_mainWindow->refresh();
    l_testWindow->loadfromfile("example.txt");
    m_mainWindow->drawAt(4, 4, "Testing 2");

    m_terosScreen->displayscr();
    
    m_initialized = true;
}


void TerosTestInterface::run(){

//    m_terosScreen->displayscr();
//    l_testWindow->loadfromfile("example.txt");
    
}


void TerosTestInterface::handleKeys(int input){
    
    
    
}