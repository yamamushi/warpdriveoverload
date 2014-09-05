//
//  shell.cpp
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 8/28/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//

#include "shell.h"
#include "window.h"
#include "version.h"
#include "graphchart.h"
#include "tr1_threading.h"
#include "navigation.h"
#include "debugWindow.h"

#include "asciicodes.h"
#include "terostest.h"

#include <algorithm>

void Shell::boot(){
    
    std::cout << "Welcome to Warp Core Overloaded" << std::endl;
    sleep(1);
    std::cout << "Please standby for Nostradamus OS boot" << std::endl;
    sleep(1);
    term_clear();
    init();
    
}


void Shell::refreshShell(){
    
    getmaxyx(stdscr,m_rows,m_cols);
    
    for(size_t x = 0; x < m_windows.size(); x++){
        m_windows.at(x)->resize(m_rows, m_cols, 0, 0);
    }
    
    if(m_topInterface){
        m_topInterface->getWindow()->clearScreen();
        m_topInterface->getWindow()->refresh();
    }
}

bool Shell::init(){
    
    initscr();
    
    if(has_colors() == FALSE)
	{
        endwin();
        std::cout << "Your terminal does not support color\n" << std::endl;
		exit(1);
	}

    getmaxyx(stdscr,m_rows,m_cols);

    
    //raw(); // disable line buffering
    cbreak();			// Line buffering disabled, Pass on
    keypad(stdscr, TRUE);		/* We get F1, F2 etc..		*/
    noecho();			/* Don't echo() while we do getch */
    start_color();			/* Start color 			*/
    curs_set(0);
    refresh();
        
    return true;
    
}



bool Shell::run(){
    
    initMainWindow();
    organizeInterfaces();
    
    if(!m_topInterface){
        // Something went wrong this should not happen
        return false;
    }
    
    // This is about to get fun
    nodelay(stdscr, true);
    int keyInput;

    m_running = true;

    while(m_running)
	{
        refresh();
        doupdate();
        
        if((keyInput = getch()) == ERR){
            execute();
        }
        else{
            handleKeys(keyInput);
        }
    }
    
    shutdown();
    
    return true;
}




void Shell::initMainWindow(){

    m_topInterface = m_interfaceList.at(0);
    keypad(stdscr, TRUE);		/* We get F1, F2 etc..		*/
    m_topInterface->init();
    
}

void Shell::execute(){
    
    if(checkForResize()){
        m_topInterface->getWindow()->clearScreen();
        m_topInterface->getWindow()->resize(m_rows, m_cols, 0, 0);
        m_topInterface->getWindow()->refresh();
    }

    if(!m_topInterface->initialized()){
        m_topInterface->getWindow()->clearScreen();
        m_topInterface->init();
    }
    
    
    // We give priority to the window render over the interface running, as we want to make sure our widgets
    // And Menus have a chance to run before we do any manual drawing to the screen through the interface
    
    m_topInterface->getWindow()->render();
    m_topInterface->run();
    //m_topInterface->getWindow()->render();
    
}


void Shell::handleKeys(int input){
    
    switch(input)
    {
        case KEY_TAB: // This is defined in asciicodes.h
            m_topInterface->getWindow()->clearScreen();
            m_topInterface->getWindow()->refresh();
            m_topInterface = m_topInterface->getNext();
            m_topInterface->getWindow()->clearScreen();
            break;
            
        default:
            m_topInterface->handleKeys(input);
            break;
    }
}



bool Shell::checkForResize(){
    
    int newRows, newCols;
    
    getmaxyx(stdscr, newRows, newCols);

    if(newRows != m_rows || newCols != m_cols){
        m_rows = newRows;
        m_cols = newCols;
        return true;
    }
    else
        return false;
}


void Shell::loadInterfaces(_SharedPtr<Shell> parent){
    
    // Launch our debug Interface which will attach to the root Interface on this shell
    _SharedPtr<DebugInterface> debugInterface(new DebugInterface(parent));
    addToInterfaceList(debugInterface);
    
    _SharedPtr<NavigationInterface> navigationInterface(new NavigationInterface(parent));
    addToInterfaceList(navigationInterface);

    _SharedPtr<TerosTestInterface> terosTest(new TerosTestInterface(parent));
    addToInterfaceList(terosTest);
    
    initMainWindow();

}

void Shell::populateInterfaces(){
    
    organizeInterfaces();
    
}



void Shell::printDebug(){
    
    mvwprintw(stdscr, m_rows/2, m_cols/2, "%s", "Testing Debug Output");
    
}



void Shell::quit(){
    
    m_running = false;
    
}



void Shell::addToInterfaceList(_SharedPtr<Interface> target){
    
    m_interfaceList.push_back(target);

    size_t InterfaceListSize = m_interfaceList.size();

    if(InterfaceListSize > 0){
        
        m_interfaceList.at(InterfaceListSize-1)->addNext(m_interfaceList.back());
        m_interfaceList.back()->addPrev(m_interfaceList.at(InterfaceListSize-1));
        m_interfaceList.back()->addNext(m_interfaceList.at(0));
        
    }
}



void Shell::organizeInterfaces(){
    
    size_t InterfaceListSize = m_interfaceList.size();
    
    for(size_t x = 0; x < m_interfaceList.size(); x++){
        
        if(x > 0){

            m_interfaceList.at(x-1)->addNext(m_interfaceList.at(x));
            m_interfaceList.at(x)->addPrev(m_interfaceList.at(x-1));
            
        }
        else{
            m_interfaceList.back()->addNext(m_interfaceList.at(0));
            m_interfaceList.back()->addPrev(m_interfaceList.at(0));
        }
    }
    
    m_interfaceList.back()->addPrev(m_interfaceList.at(InterfaceListSize-2));
    m_interfaceList.back()->addNext(m_interfaceList.at(0));
    
}



void Shell::createWindow(int ysize, int xsize){
    
    _SharedPtr<ncursesWindow> new_window = _SharedPtr<ncursesWindow>(new ncursesWindow(m_rows, m_cols, 0, 0)); // Initialize our root window
    m_windows.push_back(new_window); // Add to the list of Windows for the window manager.
    
}


void Shell::addToWindowList(_SharedPtr<ncursesWindow> target){
    
    m_windows.push_back(target); // Add to the list of Windows for the window manager.
    
}


void Shell::removeFromInterfaceList(_SharedPtr<Interface> target){
    
    std::vector<_SharedPtr<Interface>>::iterator it = std::find(m_interfaceList.begin(), m_interfaceList.end(), target);
    if (it != m_interfaceList.end()){
        m_interfaceList.erase(std::remove(m_interfaceList.begin(), m_interfaceList.end(), target), m_interfaceList.end());
    }
    
}



void Shell::removeFromWindowList(_SharedPtr<ncursesWindow> target){
    
    std::vector<_SharedPtr<ncursesWindow>>::iterator it = std::find(m_windows.begin(), m_windows.end(), target);
    if (it != m_windows.end()){
        m_windows.erase(std::remove(m_windows.begin(), m_windows.end(), target), m_windows.end());
    }
    
}



void Shell::shutdown(){
    
    for(size_t x = 0; x < m_windows.size(); x++){
        m_windows.at(x)->close();
        
    }
    endwin();
    
}


void Shell::close_win(_SharedPtr<ncursesWindow> target_window){
    
    target_window->close();
    
}
