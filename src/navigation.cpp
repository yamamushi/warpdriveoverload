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
#include "shell.h"

#include <vector>
#include <ncurses.h>
#include <ctime>


void NavigationInterface::init(){
    
    // By the time we get here, we should have already have had a window created and ready for us.
    m_mainWindow->clearScreen();

    // Set our Interface NAme
    setName("Navigation");
    
    
    // Add widgets
    m_graphX = 1;
    m_graphY = 1;
    lotteryLimit = 100;
    graphController = _SharedPtr<GraphChart>(new GraphChart(m_mainWindow, m_graphX, m_graphY));
    m_mainWindow->addWidget(graphController);
    

    // Here we populate our random points
//    _STD_FUNCTION(void(int,int)) pass = _STD_BIND(&NavigationInterface::drawAt, this, std::placeholders::_1, std::placeholders::_2);
//    _STD_FUNCTION(void(int,int)) fail = _STD_BIND(&NavigationInterface::failedAt, this, std::placeholders::_1, std::placeholders::_2);
//    _STD_FUNCTION(void(int,int)) fail2 = _STD_BIND(void,nullptr, std::placeholders::_1, std::placeholders::_2);
    int height = m_mainWindow->getY();
    int width = m_mainWindow->getX();

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
    
    
    
    std::vector<std::pair<std::string, _STD_FUNCTION(void()) > > navigationMenuList;
    std::pair<std::string, _STD_FUNCTION(void())> Menu("Menu", _STD_BIND(&NavigationInterface::doNothing, this));
    navigationMenuList.push_back(Menu);
    std::pair<std::string, _STD_FUNCTION(void())> item2("Second", _STD_BIND(&NavigationInterface::doNothing, this));
    navigationMenuList.push_back(item2);
    std::pair<std::string, _STD_FUNCTION(void())> item3("Third", _STD_BIND(&NavigationInterface::doNothing, this));
    navigationMenuList.push_back(item3);
    std::pair<std::string, _STD_FUNCTION(void())> item5("Exit", _STD_BIND(&Shell::quit, m_owner));
    navigationMenuList.push_back(item5);
    
    
    menuNavigation = _SharedPtr<ncursesMenu>(new ncursesMenu(navigationMenuList, "Navigation", m_mainWindow));

    menuNavigation->showTitle(false);
    menuNavigation->highlightTitle(false);
    menuNavigation->setHorizontal(true);
    menuNavigation->move(height-3,5);
    m_mainWindow->addMenu(menuNavigation);
    /*
    std::vector<std::pair<std::string, _STD_FUNCTION(void()) > > subMenuList;
    std::pair<std::string, _STD_FUNCTION(void())> subItem1("Sub1", _STD_BIND(&NavigationInterface::doNothing, this));
    std::pair<std::string, _STD_FUNCTION(void())> subItem2("Sub2", _STD_BIND(&NavigationInterface::doNothing, this));
    subMenuList.push_back(subItem1);
    subMenuList.push_back(subItem2);
    
    _SharedPtr<ncursesMenu> subList(new ncursesMenu(subMenuList, "Sub", m_mainWindow));
    

    menuEngineering->addSubMenu(subList, 2);
     */



    graphController->hideBars();
    graphController->refresh();
    m_initialized = true;
    
}


void NavigationInterface::drawAt(int x, int y){
    
    if(y == -1 || x == -1)
        return;
    
    init_pair(5, COLOR_GREEN, COLOR_BLACK); // A default Background Color

    _SharedPtr<GraphChartPoint> point(new GraphChartPoint(x,y,COLOR_PAIR(5),"*"));
    graphController->addRawChartPoint(point);
    
}


void NavigationInterface::run(){
    
    //randDirection();
    // Print our name out to the Interface
    mvwprintw(m_mainWindow->get(), 1, (m_sizeY - getName().size())/2, "%s", getName().c_str());
    std::string rowMessage = std::to_string(graphController->getRows()) + " : Rows";
    std::string colMessage = std::to_string(graphController->getCols()) + " : Cols";

    mvwprintw(m_mainWindow->get(), 1, (graphController->getCols()/2)-getName().length(),"%s", rowMessage.c_str());
    
    mvwprintw(m_mainWindow->get(), 2, (graphController->getCols()/2)-getName().length(),"%s", colMessage.c_str());
    
    time_t timeT = time(0);
    struct tm * now = localtime( & timeT );
    char       buf[80];
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", now);
    
    std::string timeString(buf);
    std::string timeMessage = "Time: " + timeString;

    
    mvwprintw(m_mainWindow->get(), 1, (graphController->getCols()/2)-getName().length()+18,"%s", timeMessage.c_str());

    
    m_mainWindow->render();
    
}


void NavigationInterface::handleKeys(int input){
    
    //mvwprintw(m_mainWindow->get(), 10, 2,"%d", input);

    switch(input){
        case KEY_DOWN:
      /*      graphController->resize(m_graphX, m_graphY+1);
            m_graphY = graphController->getYSize();
            m_graphX = graphController->getXSize();
            graphController->refresh(); */
            break;
            
        case KEY_UP:
       /*     graphController->resize(m_graphX, m_graphY-1);
            m_graphY = graphController->getYSize();
            m_graphX = graphController->getXSize();
            graphController->refresh(); */
            break;
            
        case KEY_LEFT:
          /*  graphController->resize(m_graphX-1, m_graphY);
            m_graphY = graphController->getYSize();
            m_graphX = graphController->getXSize();
            graphController->refresh(); */
            menuNavigation->selectPrev();
            break;
            
        case KEY_RIGHT:
           /* graphController->resize(m_graphX+1, m_graphY);
            m_graphY = graphController->getYSize();
            m_graphX = graphController->getXSize();
            graphController->refresh();*/
            menuNavigation->selectNext();
            break;
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
        case '\n':
            //;//graphController->getAllChartPoints().at(0)->m_hidden = !m_chartPoints.at(0)->m_hidden;
            menuNavigation->execute();
            break;
        default:
            m_mainWindow->handleKeys(input);
            break;
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
