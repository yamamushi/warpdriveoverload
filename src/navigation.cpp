//
//  navigation.cpp
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 8/29/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//

#include "navigation.h"
#include "widget.h"
#include "graphchart.h"
#include "tr1_wrapper.h"
#include "bresenham2d.h"
#include "tr1_threading.h"
#include "connectionwidget.h"
#include "TimeWidget.h"
#include "shell.h"

#include <vector>
#include <ncurses.h>

#include <iostream>


void NavigationInterface::init(){
    
    // By the time we get here, we should have already have had a window created and ready for us.
    m_mainWindow->clearScreen();

    // Set our Interface NAme
    setName("Navigation");
    
    // Add widgets
    m_graphX = 1;
    m_graphY = 1;
    lotteryLimit = 100;
    graphController = _SharedPtr<GraphChart>(new GraphChart(m_mainWindow, 0, 0));
    m_widgetManager->addWidget(graphController);
    
    _SharedPtr<TimeWidget> w_timeWidget = _SharedPtr<TimeWidget> (new TimeWidget(m_mainWindow, (graphController->getCols()/2)-(int)getName().length()+18, 1));
    m_widgetManager->addWidget(w_timeWidget);

    // Here we populate our random points
//    _STD_FUNCTION(void(int,int)) pass = _STD_BIND(&NavigationInterface::drawAt, this, std::placeholders::_1, std::placeholders::_2);
//    _STD_FUNCTION(void(int,int)) fail = _STD_BIND(&NavigationInterface::failedAt, this, std::placeholders::_1, std::placeholders::_2);
//    _STD_FUNCTION(void(int,int)) fail2 = _STD_BIND(void,nullptr, std::placeholders::_1, std::placeholders::_2);

    //graphController->move(3, 3);
    //graphController->resizeWindow(10, 20);
    
    _SharedPtr<GraphChartPoint> point(new GraphChartPoint( 3, 3, "O", COLOR_RED, COLOR_BLACK));
    graphController->addChartPoint(point);
    
/*
    // Bottom Left
    //bresenham2d(5, rows-5, cols-5, 3, _STD_BIND(&NavigationInterface::drawAt, this, std::placeholders::_1, std::placeholders::_2));
    // Top Right
    bresenham2d(width-6, 4, width-6, height-5, _STD_BIND(&NavigationInterface::drawAt, this, std::placeholders::_1, std::placeholders::_2));
    // Bottom Right
    //bresenham2d(cols-5, rows-5, 5, 3, _STD_BIND(&NavigationInterface::drawAt, this, std::placeholders::_1, std::placeholders::_2));
    // Left
    bresenham2d(5, 4, 5, height-5, _STD_BIND(&NavigationInterface::drawAt, this, std::placeholders::_1, std::placeholders::_2));
    // Bottom Left
    bresenham2d(5, 4, width-6, 4, _STD_BIND(&NavigationInterface::drawAt, this, std::placeholders::_1, std::placeholders::_2));
    // Bottom
    bresenham2d(5, height-5, width-6, height-5, _STD_BIND(&NavigationInterface::drawAt, this, std::placeholders::_1, std::placeholders::_2));
    m_mainWindow->hideBorder();
    
    */
    
    std::vector<std::pair<std::string, _STD_FUNCTION(void()) > > navigationMenuList;
    std::pair<std::string, _STD_FUNCTION(void())> Menu("Menu", _STD_BIND(&NavigationInterface::doNothing, this));
    navigationMenuList.push_back(Menu);

  
    m_mainWindow->hideBorder();

    
    std::vector<std::pair<std::string, _STD_FUNCTION(void()) > > subMenuList;
    std::pair<std::string, _STD_FUNCTION(void())> itemExit("Exit", _STD_BIND(&Shell::quit, m_owner));
    subMenuList.push_back(itemExit);


    graphController->hideBars();
    graphController->refresh();
    
    testString = "";
    
    m_initialized = true;
    
}


void NavigationInterface::drawAt(int x, int y){
    
    if(y == -1 || x == -1)
        return;
    
    //init_pair(5, COLOR_GREEN, COLOR_BLACK); // A default Background Color

    _SharedPtr<GraphChartPoint> point(new GraphChartPoint(x, y, "*"));
    graphController->addRawChartPoint(point);
    
}


void NavigationInterface::run(){
    
    // Print our name out to the Interface
    m_mainWindow->drawAt( (m_sizeY - (int)getName().size())/2, 1, getName(), COLOR_WHITE, COLOR_BLACK, A_BOLD | A_BLINK);
    
    std::string rowMessage = std::to_string(graphController->getRows()) + " : Rows";
    std::string colMessage = std::to_string(graphController->getCols()) + " : Cols";
    m_mainWindow->drawAt((m_mainWindow->getX()/2)-(int)getName().length(), 1, rowMessage);
    m_mainWindow->drawAt((m_mainWindow->getX()/2)-(int)getName().length(), 2, colMessage);
    
    m_mainWindow->drawAt((m_mainWindow->getX()-10), 1, "           ");
    std::string fpscount(std::to_string(m_owner->getfps()) + " fps");
    m_mainWindow->drawAt((m_mainWindow->getX()-2)-(int)fpscount.length(), 1, fpscount);

    m_mainWindow->drawAt((m_mainWindow->getX()/2), (m_mainWindow->getY()/2), testString);

    m_mainWindow->render();
    
}


void NavigationInterface::handleKeys(int input){
    
    switch(input){
        case 'b':
            graphController->toggleBars();
            m_mainWindow->clearScreen();
            graphController->refresh();
            break;
        case 'B':
            m_mainWindow->toggleBorder();
            m_mainWindow->clearScreen();
            graphController->refresh();
            break;
        case 'i':
            lotteryLimit = lotteryLimit + 100000;
            break;
        case 'u':
            lotteryLimit = lotteryLimit - 100000;
            break;
        default:
            m_widgetManager->handleKeys(input);
            break;
    }
    
}


void NavigationInterface::getInput(){
   
    while(int input = getch() ){
        
        if(input == '\n' || input == 27)
            break;
        
        if(input > 0){
            
            if(input == KEY_BACKSPACE || input == KEY_DC || input == 127)
                testString.pop_back();
            else
                testString += input;
        
            //m_mainWindow->drawAt((m_mainWindow->getX()/2), (m_mainWindow->getY()/2), "             ");
            m_mainWindow->clearLine( (m_mainWindow->getY()/2), (m_mainWindow->getX()/2));
            
            m_mainWindow->drawAt((m_mainWindow->getX()/2), (m_mainWindow->getY()/2), testString);
        
        }
        m_mainWindow->render();
        
        input = 0;
    }
    
}



void NavigationInterface::randDirection(){
    
    
    int lottery = rand() % lotteryLimit;
    if(lottery > lotteryLimit - 50 ){
        int number = rand() % graphController->getAllChartPoints().size();
        _SharedPtr<GraphChartPoint> point1 = graphController->getAllChartPoints().at(number);
        if(point1){
            
            int direction = rand() % 9 + 1;
            
            
            switch(direction){
                case 1:
                    graphController->removePoint(point1);
                    if(point1->m_X > 0)
                        point1->m_X--;
                    if(point1->m_Y < graphController->getRows()-1)
                        point1->m_Y++;
                    break;
                case 2:
                    graphController->removePoint(point1);
                    if(point1->m_Y < graphController->getRows()-1)
                        point1->m_Y++;
                    break;
                case 3:
                    graphController->removePoint(point1);
                    if(point1->m_X < graphController->getCols())
                        point1->m_X++;
                    if(point1->m_Y < graphController->getRows()-1)
                        point1->m_Y++;
                    break;
                case 4:
                    graphController->removePoint(point1);
                    if(point1->m_X > 0)
                        point1->m_X--;
                    break;
                case 5:
                    break;
                case 6:
                    graphController->removePoint(point1);
                    if(point1->m_X < graphController->getCols())
                        point1->m_X++;
                    break;
                case 7:
                    graphController->removePoint(point1);
                    if(point1->m_X > 0)
                        point1->m_X--;
                    if(point1->m_Y > 0)
                        point1->m_Y--;
                    break;
                case 8:
                    graphController->removePoint(point1);
                    if(point1->m_Y > 0)
                        point1->m_Y--;
                    break;
                case 9:
                    graphController->removePoint(point1);
                    if(point1->m_X < graphController->getCols())
                        point1->m_X++;
                    if(point1->m_Y > 0)
                        point1->m_Y--;
                    break;
            }
            
        }
    }
}
