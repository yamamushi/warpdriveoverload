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

    getmaxyx(stdscr, m_sizeY, m_sizeX);
    
    // Build a panel first
    m_panel = _SharedPtr<ncursesPanel>(new ncursesPanel(_SharedPtr<ncursesWindow>(new ncursesWindow(m_sizeY, m_sizeX, 0, 0))));
    
    // Assign our main window
    m_mainWindow = m_panel->getChild();
    
    // Set our Panel NAme
    m_panel->setName("Navigation");
    
    // Print our name out to the panel
    mvwprintw(m_panel->getChild()->get(), 1, (m_sizeY - m_panel->getName().size())/2, "%s", m_panel->getName().c_str());

    
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
    temp->hideBars();
    //graphController->resize(m_sizeY, m_sizeX);
    
    m_owner->addToInterfaceList(shared_from_this());
    
    m_mainWindow->clearScreen();
    m_mainWindow->refresh();
    m_mainWindow->render();
    
}


void NavigationInterface::run(){
    
    
    
}