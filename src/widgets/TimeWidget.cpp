//
//  TimeWidget.cpp
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 9/1/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//

#include "TimeWidget.h"

#include <ctime>
#include <string>

void TimeWidget::render(){
    
    time_t timeT = time(0);
    struct tm * now = localtime( & timeT );
    char       buf[80];
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", now);
    
    std::string timeString(buf);
    std::string timeMessage = "Time: " + timeString;

    m_parent->drawAt(m_xpos, m_ypos, timeMessage);
    
}

void TimeWidget::refresh(){
    
}

void TimeWidget::resize(int newx, int newy){
    
}

void TimeWidget::handleKeys(int input){
    
}