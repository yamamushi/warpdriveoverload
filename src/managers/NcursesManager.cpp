//
//  NcursesManager.cpp
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 9/7/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//

#include "NcursesManager.h"
#include "util/term_control.h"
#include "util/Clock.h"
#include <iostream>

bool NcursesManager::start(){
    
    std::cout << "Welcome to Warp Core Overloaded" << std::endl;
    sleep(1);
    std::cout << "Please standby for Nostradamus OS boot" << std::endl;
    sleep(1);
    term_clear();
    
    initscr();
    
    if(has_colors() == FALSE)
	{
        endwin();
        std::cout << "Your terminal does not support color\n" << std::endl;
		return false;
	}
    
    getmaxyx(stdscr,m_rows,m_cols);
    
    
    //raw(); // disable line buffering
    cbreak();			// Line buffering disabled, Pass on
    keypad(stdscr, TRUE);		/* We get F1, F2 etc..		*/
    noecho();			/* Don't echo() while we do getch */
    start_color();			/* Start color 			*/
    curs_set(0);
    refresh();
    
    keypad(stdscr, TRUE);		/* We get F1, F2 etc..		*/

    return true;
    
}

int NcursesManager::getfps(){
    
    int fps = FpsCounter::Instance()->get();
    
    return fps;
    
}

int NcursesManager::getWidth(){
    
    getmaxyx(stdscr,m_rows,m_cols);
    return m_cols;
    
}

int NcursesManager::getHeight(){
    getmaxyx(stdscr,m_rows,m_cols);
    return m_rows;
}

void NcursesManager::setmaxfps(int fps){
    
        if(fps < 1)
            fps = 1;
        
        if(fps > 1000)
            fps = 1000;
        
        m_maxfps = fps;
        
        timeout(1000/m_maxfps);

}