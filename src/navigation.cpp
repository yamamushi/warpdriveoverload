//
//  navigation.cpp
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 8/29/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//

#include "navigation.h"
#include "widget.h"


void NavigationInterface::init(){
    
    // By the time we get here, we should have already have had a window created and ready for us.
    m_mainWindow->clearScreen();

    // Set our Interface NAme
    setName("Navigation");
    
    // Print our name out to the Interface
    mvwprintw(m_mainWindow->get(), 1, (m_sizeY - getName().size())/2, "%s", getName().c_str());
    
    // Add widgets
    _SharedPtr<GraphChart> graphController = _SharedPtr<GraphChart>(new GraphChart(m_mainWindow, 2, 1));
    m_mainWindow->addWidget(graphController);
    
    
    // Here we populate our
    init_pair(3, COLOR_RED, COLOR_BLACK); // A default Background Color
    _SharedPtr<GraphChartPoint> point1(new GraphChartPoint(5,8,3,"*"));
    init_pair(8, COLOR_BLUE, COLOR_BLACK); // A default Background Color
    _SharedPtr<GraphChartPoint> point2(new GraphChartPoint(2,9,8,"*"));
    init_pair(9, COLOR_YELLOW, COLOR_BLACK); // A default Background Color
    _SharedPtr<GraphChartPoint> point3(new GraphChartPoint(0,2,9,"*"));
    init_pair(10, COLOR_WHITE, COLOR_BLACK); // A default Background Color
    _SharedPtr<GraphChartPoint> point4(new GraphChartPoint(1,3,10,"*"));
    init_pair(11, COLOR_CYAN, COLOR_BLACK); // A default Background Color
    _SharedPtr<GraphChartPoint> point5(new GraphChartPoint(8,1,11,"*"));
    
    _SharedPtr<GraphChart> temp = std::dynamic_pointer_cast<GraphChart>(graphController);
    temp->addChartPoint(point1);
    temp->addChartPoint(point2);
    temp->addChartPoint(point3);
    temp->addChartPoint(point4);
    temp->addChartPoint(point5);
    
    _SharedPtr<GraphChartPoint> point6(new GraphChartPoint(8,1,11,"@"));
    temp->addRawChartPoint(point6);
    //temp->hideBars();
    //graphController->resize(m_sizeY, m_sizeX);
    graphController->refresh();
    m_initialized = true;
    
}


void NavigationInterface::run(){
    
    
    
}


void NavigationInterface::handleKeys(int input){
    
    m_mainWindow->handleKeys(input);

}

