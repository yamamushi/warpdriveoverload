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
    
    raw(); // disable line buffering
    cbreak();			// Line buffering disabled, Pass on
    keypad(stdscr, TRUE);		/* We get F1, F2 etc..		*/
    noecho();			/* Don't echo() while we do getch */
    start_color();			/* Start color 			*/
    curs_set(0);
    refresh();
    
    getmaxyx(stdscr,m_rows,m_cols);
    
    return true;
    
}



bool Shell::run(){
    
    initMainWindow();
    populateInterfaces();
    
    if(!m_topInterface){
        // Something went wrong this should not happen
        return false;
    }
    
    // Our first window is now about to be replaced
    //m_topInterface = m_topInterface->getNext();
    
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
    
    m_topInterface->run();
    
    m_topInterface->getWindow()->render();
    
}


void Shell::handleKeys(int input){
    
    switch(input)
    {
        case KEY_TAB: // This is defined in asciicodes.h
            m_topInterface->getWindow()->clearScreen();
            m_topInterface->getWindow()->refresh();
            m_topInterface->getWindow()->closeAllMenus();
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
    //debugInterface->init();
    
    _SharedPtr<NavigationInterface> navigationInterface(new NavigationInterface(parent));
    addToInterfaceList(navigationInterface);
    //navigationInterface->init();

    initMainWindow();

}

void Shell::populateInterfaces(){
    
    //wrefresh(m_mainWindow->get());
	//refresh();
    
    //wclear(m_topInterface->getChild()->get());
    /*
    
    m_Interfaces.at(2)->setName("Engineering");
    
    std::vector<std::pair<std::string, _STD_FUNCTION(void()) > > menuList;
    std::pair<std::string, _STD_FUNCTION(void())> item("First", _STD_BIND(&Shell::doNothing, this));
    menuList.push_back(item);
    std::pair<std::string, _STD_FUNCTION(void())> item2("Second", _STD_BIND(&Shell::doNothing, this));
    menuList.push_back(item2);
    std::pair<std::string, _STD_FUNCTION(void())> item3("Third", _STD_BIND(&Shell::doNothing, this));
    menuList.push_back(item3);
    std::pair<std::string, _STD_FUNCTION(void())> item4("Fourth", _STD_BIND(&Shell::printDebug, this));
    menuList.push_back(item4);
    std::pair<std::string, _STD_FUNCTION(void())> item5("Exit", _STD_BIND(&Shell::quit, this));
    menuList.push_back(item5);
    
    std::vector<std::pair<std::string, _STD_FUNCTION(void()) > > subMenuList;
    std::pair<std::string, _STD_FUNCTION(void())> subItem1("Sub1", _STD_BIND(&Shell::doNothing, this));
    std::pair<std::string, _STD_FUNCTION(void())> subItem2("Sub2", _STD_BIND(&Shell::doNothing, this));
    subMenuList.push_back(subItem1);
    subMenuList.push_back(subItem2);
    
    _SharedPtr<ncursesMenu> subList(new ncursesMenu(subMenuList, "Sub", m_Interfaces.at(2)->getChild()));
    
    _SharedPtr<ncursesMenu> menuEngineering(new ncursesMenu(menuList, "ENG", m_Interfaces.at(2)->getChild()));
    menuEngineering->showTitle(true);
    menuEngineering->highlightTitle(true);
    menuEngineering->move(10,10);
    menuEngineering->addSubMenu(subList, 2);
    
    init_pair(1, COLOR_RED, COLOR_BLACK); // A default Background Color
    menuEngineering->setSelectedColor(COLOR_PAIR(1));
    menuEngineering->render();
    _SharedPtr<ncursesMenu> menuMain(new ncursesMenu(menuList, "MAIN", m_Interfaces.at(0)->getChild(), true));
    menuMain->render();
    
    std::vector<std::pair<std::string, _STD_FUNCTION(void()) > > subMenuList2;
    std::pair<std::string, _STD_FUNCTION(void())> subItem3("Sub1", _STD_BIND(&Shell::doNothing, this));
    std::pair<std::string, _STD_FUNCTION(void())> subItem4("Sub2", _STD_BIND(&Shell::doNothing, this));
    subMenuList2.push_back(subItem3);
    subMenuList2.push_back(subItem4);
    _SharedPtr<ncursesMenu> subList2(new ncursesMenu(subMenuList2, "Sub", m_Interfaces.at(0)->getChild()));
    menuMain->addSubMenu(subList2, 2);
    
    std::vector<std::pair<std::string, _STD_FUNCTION(void()) > > subMenuList3;
    std::pair<std::string, _STD_FUNCTION(void())> subItem5("Sub1", _STD_BIND(&Shell::doNothing, this));
    std::pair<std::string, _STD_FUNCTION(void())> subItem6("Sub2", _STD_BIND(&Shell::doNothing, this));
    subMenuList3.push_back(subItem5);
    subMenuList3.push_back(subItem6);
    _SharedPtr<ncursesMenu> subList3(new ncursesMenu(subMenuList3, "Sub", m_Interfaces.at(0)->getChild()));
    menuMain->addSubMenu(subList3, 3);
    
    
    //m_Interfaces.at(0)->getChild()->addMenu(menuMain);
    //m_Interfaces.at(2)->getChild()->addMenu(menuEngineering);
     */
    
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
