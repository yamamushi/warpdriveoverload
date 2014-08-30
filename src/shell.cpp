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
#include "ncursespanel.h"
#include "graphchart.h"
#include "tr1_threading.h"

#include "debugWindow.h"

#include "asciicodes.h"


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
    
    if(m_topPanel){
        m_topPanel->getChild()->clearScreen();
        m_topPanel->getChild()->refresh();
    }
}

bool Shell::init(){
    
    m_running = true;
    
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
    
    //mvwprintw(stdscr, 4, (m_cols - m_topPanel->getName().size())/, "%s", m_topPanel->getName().c_str());
    populatePanels();
    if(!m_topPanel){
        // Something went wrong this should not happen
        return false;
    }
    
    // This is about to get fun
    nodelay(stdscr, true);
    int keyInput;
    
    m_topPanel->getChild()->clearScreen();
    m_topPanel->getChild()->refresh();
    m_topPanel->getChild()->render();
    
    while(m_running)
	{
        refresh();
        doupdate();
        
        if((keyInput = getch()) == ERR){
            run();
        }
        else{
            handleKeys(keyInput);
        }
    }
    wrefresh(m_mainWindow->get());
    return true;
}


void Shell::run(){
    
    if(checkForResize()){
        m_topPanel->getChild()->clearScreen();
        m_topPanel->getChild()->refresh();
    }
    
    m_topPanel->getChild()->render();
    //mvwprintw(m_topPanel->getChild()->get(), 1, (m_cols - m_topPanel->getName().size())/2, "%s", m_topPanel->getName().c_str());
}


void Shell::handleKeys(int input){
    
    switch(input)
    {
        case KEY_F(1):
            m_topPanel = m_panels.at(1);
            wclear(m_topPanel->getChild()->get());
            mvwprintw(m_topPanel->getChild()->get(), 1, (m_cols - m_topPanel->getName().size())/2, "%s", m_topPanel->getName().c_str());
            break;
            
        case KEY_F(2):
            m_topPanel = m_panels.at(2);
            mvwprintw(m_topPanel->getChild()->get(), 1, (m_cols - m_topPanel->getName().size())/2, "%s", m_topPanel->getName().c_str());
            break;
            
        case KEY_F(3):
            m_topPanel = m_panels.at(0);
            wclear(m_topPanel->getChild()->get());
            break;
            
        case KEY_TAB: // This is defined in asciicodes.h
            m_topPanel->getChild()->closeAllMenus();
            m_topPanel->getChild()->clearScreen();
            m_topPanel = m_topPanel->getNext();
            m_topPanel->getChild()->clearScreen();
            m_topPanel->getChild()->refresh();
            break;
            
        default:
            m_topPanel->getChild()->handleKeys(input);
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


void Shell::loadInterfaces(){
    
    
    
}

void Shell::populatePanels(){
    
    createWindow(m_rows, m_cols); // Create our root window
    m_mainWindow = m_windows.at(0); // Assign it here
    addToPanelList(m_mainWindow); // Add our window to the panel list manually
    //m_panels.at(0)->setName("Debug Window");
    
    init_pair(1, COLOR_GREEN, COLOR_BLACK); // A default Background Color
    wbkgd(m_mainWindow->get(), COLOR_PAIR(1)); // Set the background color accordingly
    std::string welcome = "Welcome to Nostradamus OS";
    attroff(A_BOLD);
    mvwprintw(m_mainWindow->get(), (m_rows/2)-1, (m_cols - welcome.size())/2, "%s", welcome.c_str());
    mvwprintw(m_mainWindow->get(), m_rows/2,(m_cols - global_version_string.size())/2,"%s", global_version_string.c_str());
    wattron(m_mainWindow->get(), A_BLINK);
    std::string pleasecontinue = "Press any key to Continue";
    mvwprintw(m_mainWindow->get(), m_rows-5,(m_cols - pleasecontinue.size())/2,"%s", pleasecontinue.c_str());
    wattroff(m_mainWindow->get(), A_BLINK);
    wrefresh(m_mainWindow->get());
    refresh();
    getch();
    
    
    
    
    keypad(m_mainWindow->get(), TRUE);		/* We get F1, F2 etc..		*/
    
    wrefresh(m_mainWindow->get());
	refresh();
    
    
    
    
    
    createWindow(m_rows, m_cols);
    addToPanelList(m_windows.at(1));
    
    createWindow(m_rows, m_cols);
    addToPanelList(m_windows.at(2));
    
    m_topPanel = m_panels.at(0);
    
    wclear(m_topPanel->getChild()->get());
    mvwprintw(m_topPanel->getChild()->get(), 1, (m_cols - m_topPanel->getName().size())/2, "%s", m_topPanel->getName().c_str());
    //top_panel(m_topPanel->getPanel());
    
    
    
    
    m_panels.at(1)->setName("Navigation");
    
    graphController = _SharedPtr<GraphChart>(new GraphChart(m_windows.at(1), 2, 1));
    m_windows.at(1)->addWidget(graphController);
    graphController->setParent(m_windows.at(1));
    
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

    
    
    m_panels.at(2)->setName("Engineering");
    
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
    
    _SharedPtr<ncursesMenu> subList(new ncursesMenu(subMenuList, "Sub", m_panels.at(2)->getChild()));
    
    _SharedPtr<ncursesMenu> menuEngineering(new ncursesMenu(menuList, "ENG", m_panels.at(2)->getChild()));
    menuEngineering->showTitle(true);
    menuEngineering->highlightTitle(true);
    menuEngineering->move(10,10);
    menuEngineering->addSubMenu(subList, 2);
    
    init_pair(1, COLOR_RED, COLOR_BLACK); // A default Background Color
    menuEngineering->setSelectedColor(COLOR_PAIR(1));
    menuEngineering->render();
    _SharedPtr<ncursesMenu> menuMain(new ncursesMenu(menuList, "MAIN", m_panels.at(0)->getChild(), true));
    menuMain->render();
    
    std::vector<std::pair<std::string, _STD_FUNCTION(void()) > > subMenuList2;
    std::pair<std::string, _STD_FUNCTION(void())> subItem3("Sub1", _STD_BIND(&Shell::doNothing, this));
    std::pair<std::string, _STD_FUNCTION(void())> subItem4("Sub2", _STD_BIND(&Shell::doNothing, this));
    subMenuList2.push_back(subItem3);
    subMenuList2.push_back(subItem4);
    _SharedPtr<ncursesMenu> subList2(new ncursesMenu(subMenuList2, "Sub", m_panels.at(0)->getChild()));
    menuMain->addSubMenu(subList2, 2);
    
    std::vector<std::pair<std::string, _STD_FUNCTION(void()) > > subMenuList3;
    std::pair<std::string, _STD_FUNCTION(void())> subItem5("Sub1", _STD_BIND(&Shell::doNothing, this));
    std::pair<std::string, _STD_FUNCTION(void())> subItem6("Sub2", _STD_BIND(&Shell::doNothing, this));
    subMenuList3.push_back(subItem5);
    subMenuList3.push_back(subItem6);
    _SharedPtr<ncursesMenu> subList3(new ncursesMenu(subMenuList3, "Sub", m_panels.at(0)->getChild()));
    menuMain->addSubMenu(subList3, 3);
    
    
    m_panels.at(0)->getChild()->addMenu(menuMain);
    m_panels.at(2)->getChild()->addMenu(menuEngineering);
    
    organizePanels();
    
    
}

void Shell::printDebug(){
    
    mvwprintw(stdscr, m_rows/2, m_cols/2, "%s", "Testing Debug Output");
    
    
}

void Shell::quit(){
    
    m_running = false;
    
}

void Shell::addToPanelList(_SharedPtr<ncursesWindow> targetWindow){
    
    size_t panelListSize = m_panels.size();
    
    _SharedPtr<ncursesPanel> l_panel(new ncursesPanel(targetWindow));
    
    m_panels.push_back(l_panel);
    
    if(panelListSize > 0){
        
        m_panels.at(panelListSize-1)->addNext(m_panels.back());
        m_panels.back()->addPrev(m_panels.at(panelListSize-1));
        m_panels.back()->addNext(m_panels.at(0));
        
    }

    
    
}

void Shell::organizePanels(){
    size_t panelListSize = m_panels.size();
    
    for(size_t x = 0; x < m_panels.size(); x++){
        
        if(x > 0){
            //set_panel_userptr(m_panels.at(x-1)->getPanel(), m_panels.at(x)->getPanel());
            
            m_panels.at(x-1)->addNext(m_panels.at(x));
            m_panels.at(x)->addPrev(m_panels.at(x-1));
            
        }
        else{
            
            //set_panel_userptr(m_panels.at(x)->getPanel(), m_panels.at(x)->getPanel());
            
        }
        
        //replace_panel(m_topPanel->getPanel(), m_panels.at(x)->getChild()->get());
    }
    
    m_panels.back()->addPrev(m_panels.at(panelListSize-2));
    m_panels.back()->addNext(m_panels.at(0));
    
    
    //update_panels();
    //doupdate();
}

void Shell::createWindow(int ysize, int xsize){
    
    _SharedPtr<ncursesWindow> new_window = _SharedPtr<ncursesWindow>(new ncursesWindow(m_rows, m_cols, 0, 0)); // Initialize our root window
    m_windows.push_back(new_window); // Add to the list of Windows for the window manager.
    
}


void Shell::addToWindowList(_SharedPtr<ncursesWindow> target){
    
    m_windows.push_back(target); // Add to the list of Windows for the window manager.
    
}


void Shell::removeFromWindowList(_SharedPtr<ncursesWindow> target){
    
    std::vector<_SharedPtr<ncursesWindow>>::iterator it = std::find(m_windows.begin(), m_windows.end(), target);
    if (it != m_windows.end()){
        m_windows.erase(std::remove(m_windows.begin(), m_windows.end(), target), m_windows.end());
    }
    
}

void Shell::removeFromPanelList(_SharedPtr<ncursesPanel> target){
    
    std::vector<_SharedPtr<ncursesPanel>>::iterator it = std::find(m_panels.begin(), m_panels.end(), target);
    if (it != m_panels.end()){
        m_panels.erase(std::remove(m_panels.begin(), m_panels.end(), target), m_panels.end());
    }
    organizePanels();
    
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
