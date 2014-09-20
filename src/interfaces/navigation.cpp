//
//  navigation.cpp
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 8/29/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//

#include "navigation.h"
#include "widgets/widget.h"
#include "widgets/graphchart.h"
#include "tr1/tr1_wrapper.h"
#include "graphics/bresenham2d.h"
#include "tr1/tr1_threading.h"
#include "widgets/connectionwidget.h"
#include "widgets/TimeWidget.h"
#include "engine/shell.h"
#include "managers/ColorManager.h"
#include <math.h>


#include <vector>

#include <iostream>


void NavigationInterface::init(){

    m_widgetManager = _SharedPtr<WidgetManager>(new WidgetManager(this));
    // By the time we get here, we should have already have had a window created and ready for us.
    m_mainWindow->clearScreen();

    m_ticks = 0;

    m_waveTicker = 0;

    // Set our Interface NAme
    setName("Navigation");
    
    // Add widgets
    m_graphX = 1;
    m_graphY = 1;
    lotteryLimit = 100;
    graphController = _SharedPtr<GraphChartWidget>(new GraphChartWidget(m_mainWindow, 0, 0));
    m_widgetManager->addWidget(graphController);
    graphController->setSize(6, 4);
    
    _SharedPtr<TimeWidget> w_timeWidget = _SharedPtr<TimeWidget> (new TimeWidget(m_mainWindow, (graphController->getCols()/2)-(int)getName().length()+18, 1));
    m_widgetManager->addWidget(w_timeWidget);
    
    
    m_targetcenterX = m_width/2;
    m_targetcenterY = m_height/2;
    
    m_randomCenterY = m_targetcenterY;
    m_randomCenterX = m_targetcenterX;
    
    setTargetCenter(m_targetcenterX, m_targetcenterY);

    // Here we populate our random points
//    _STD_FUNCTION(void(int,int)) pass = _STD_BIND(&NavigationInterface::drawAt, this, std::placeholders::_1, std::placeholders::_2);
//    _STD_FUNCTION(void(int,int)) fail = _STD_BIND(&NavigationInterface::failedAt, this, std::placeholders::_1, std::placeholders::_2);
//    _STD_FUNCTION(void(int,int)) fail2 = _STD_BIND(void,nullptr, std::placeholders::_1, std::placeholders::_2);

    //graphController->move(3, 3);
    //graphController->resizeWindow(10, 20);
    
    //_SharedPtr<GraphChartPoint> point(new GraphChartPoint( 3, 3, "O", COLOR_RED, COLOR_BLACK));
    //graphController->addChartPoint(point);
    
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
    /*
    std::vector<std::pair<std::string, _STD_FUNCTION(void()) > > navigationMenuList;
    std::pair<std::string, _STD_FUNCTION(void())> Menu("Menu", _STD_BIND(&NavigationInterface::doNothing, this));
    navigationMenuList.push_back(Menu);
*/
  
    m_mainWindow->hideBorder();
/*
    
    std::vector<std::pair<std::string, _STD_FUNCTION(void()) > > subMenuList;
    std::pair<std::string, _STD_FUNCTION(void())> itemExit("Exit", _STD_BIND(&Shell::quit, m_owner));
    subMenuList.push_back(itemExit);
*/

    graphController->hideBars();
    graphController->refresh();
    
    testString = "";
    
    setNextPoint();
    m_initialized = true;

    m_targetcenterY = m_waveCenterY;
    m_targetcenterX = m_waveCenterX;
    
    run();
    
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
    //m_mainWindow->clearScreen();
    //m_mainWindow->refresh();
    m_mainWindow->clearArea(0, 0, m_mainWindow->getX(), m_mainWindow->getY());

    update();

    //setNextPoint();

    bool update = true;

/*
        if (m_targetcenterX > m_waveCenterX){
            m_targetcenterX--;
            update = false;
            }
        if (m_targetcenterX < m_waveCenterX){
            m_targetcenterX++;
            update = false;
        }

        if (m_targetcenterY > m_waveCenterY) {
            m_targetcenterY--;
            update = false;
        }
        if (m_targetcenterY < m_waveCenterY) {
            m_targetcenterY++;
            update = false;
        }

        if(update){
            setNextPoint();

        }
*/
        setNextPoint();



    //graphController->hideBars();
    //graphController->refresh();

    graphController->render();
    //m_widgetManager->render();

    m_mainWindow->drawAt( (m_height - (int)getName().size())/2, 1, getName(), COLOR_WHITE, COLOR_BLACK, A_BOLD | A_BLINK);
    
    std::string rowMessage = std::to_string(graphController->getRows()) + " : Rows";
    std::string colMessage = std::to_string(graphController->getCols()) + " : Cols";
    m_mainWindow->drawAt((m_mainWindow->getX()/2)-(int)getName().length(), 1, rowMessage);
    m_mainWindow->drawAt((m_mainWindow->getX()/2)-(int)getName().length(), 2, colMessage);
    
    m_mainWindow->drawAt((m_mainWindow->getX()-10), 1, "           ");
    std::string fpscount(std::to_string(m_owner->getfps()) + " fps");
    m_mainWindow->drawAt((m_mainWindow->getX()-2)-(int)fpscount.length(), 1, fpscount);

    m_mainWindow->drawAt((m_mainWindow->getX()/2), (m_mainWindow->getY()/2), testString);

    setTargetCenter(m_targetcenterX, m_targetcenterY);


}



void NavigationInterface::setNextPoint() {

    int xMin = -m_mainWindow->getX() / 2;
    int xMax = m_mainWindow->getX() / 2;
    const double PI = 3.1415927;        // constant PI
    double period = m_mainWindow->getX() / 2;
    double amplitude = 20;
    double phaseAngle = 5;
    int y = 0;
    int x = 1;


    for (x = xMin; x <= xMax; x++)    // Add the for loop here, that creates the points (x,y)
    {
        y = (int) amplitude * cos((2 * (PI) / period) * x - (2 * (PI) / period) * phaseAngle); //Calculate the sine wave
        m_mainWindow->drawAt(x + m_mainWindow->getX() / 2, y + m_mainWindow->getY() / 2, "X");
    }


    y = 0;

    if (!(m_ticks % 3)) {
        int loopCount = 0;
        for (x = xMin; x <= xMax; x++)    // Add the for loop here, that creates the points (x,y)
        {                                //one pixel at a time and then adds the points via the
            y = (int) amplitude * cos((2 * (PI) / period) * x - (2 * (PI) / period) * phaseAngle); //Calculate the sine wave
            m_mainWindow->drawAt(x + m_mainWindow->getX() / 2, y + m_mainWindow->getY() / 2, "X");

            if (loopCount == m_waveTicker) {

                m_targetcenterX = x + m_mainWindow->getX() / 2;
                m_targetcenterY = y + m_mainWindow->getY() / 2;

                if (x == xMax) {
                    m_waveTicker = 0;
                } else {
                    m_waveTicker++;
                }
                return;
            }
            else {
                loopCount++;
            }

        }

    }
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
        case 'r':
            randomizeCenter();
            break;
        case KEY_UP:
            setTargetCenter(m_targetcenterX, m_targetcenterY-1);
            break;
        case KEY_DOWN:
            setTargetCenter(m_targetcenterX, m_targetcenterY+1);
            break;
        case KEY_LEFT:
            setTargetCenter(m_targetcenterX-1, m_targetcenterY);
            break;
        case KEY_RIGHT:
            setTargetCenter(m_targetcenterX+1, m_targetcenterY);
            break;
        default:
            m_widgetManager->handleKeys(input);
            break;
    }
    
}



void NavigationInterface::update(){

    // increase the counter by one
    m_ticks++;

    // one second elapsed? (= 1000 milliseconds)
    if (m_timeKeeper.value() > 250)
    {
        // save the current counter value to m_fps
        m_secondsElapsed++;

        // reset the counter and the interval
        m_ticks    = 0;
        m_timeKeeper = Interval();
    }

    if(m_secondsElapsed > 3){

        // Do stuff

        m_secondsElapsed = 0;

    }

}



void NavigationInterface::randomizeCenter(){
    
    
    int centerX = rand() % m_width;
    int centerY = rand() % m_height;
    
    m_randomCenterX = centerX;
    m_randomCenterY = centerY;
    
}


void NavigationInterface::setTargetCenter(int x, int y){
    
    if(x < 0)
        x = 0;
    if(x > m_width)
        x = m_width;
    if(y < 0)
        y = 0;
    if(y > m_height)
        y = m_height;
    
    m_targetcenterX = x;
    m_targetcenterY = y;
    
    m_mainWindow->drawLine((x), 1, (x), (m_height), "|", m_mainWindow->getBorderColorfg(), m_mainWindow->getBorderColorbg());
    m_mainWindow->drawLine(1, y, (m_width), y, "-", m_mainWindow->getBorderColorfg(), m_mainWindow->getBorderColorbg());
    
    m_mainWindow->drawAt(x, y, "#", m_mainWindow->getBorderColorfg(), m_mainWindow->getBorderColorbg());
    
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
            m_mainWindow->clearLineFrom( (m_mainWindow->getY()/2), (m_mainWindow->getX()/2));
            
            m_mainWindow->drawAt((m_mainWindow->getX()/2), (m_mainWindow->getY()/2), testString);
        
        }
        m_mainWindow->render();
        
        input = 0;
    }
    
}



void NavigationInterface::randDirection(){
    
    
    int lottery = rand() % lotteryLimit;
    if(lottery > lotteryLimit - 50 ){
        int number = (int) (rand() % graphController->getAllChartPoints().size());
        _SharedPtr<GraphChartPoint> point1 = graphController->getAllChartPoints().at((unsigned long) number);
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
                default:
                    break;
            }
            
        }
    }
}
