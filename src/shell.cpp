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

#include "asciicodes.h"


void Shell::SetStdinEcho(bool enable){
    
#ifdef WIN32
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hStdin, &mode);
    
    if( !enable )
        mode &= ~ENABLE_ECHO_INPUT;
    else
        mode |= ENABLE_ECHO_INPUT;
    
    SetConsoleMode(hStdin, mode );
    
#else
    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    if( !enable )
        tty.c_lflag &= ~ECHO;
    else
        tty.c_lflag |= ECHO;
    
    (void) tcsetattr(STDIN_FILENO, TCSANOW, &tty);
#endif
    
}



void Shell::boot(){
    
    std::cout << "Welcome to Warp Core Overloaded" << std::endl;
    sleep(1);
    std::cout << "Please standby for Nostradamus OS boot" << std::endl;
    sleep(1);
    term_clear();
    init();
    
}


bool Shell::init(){
    
    m_running = true;
    
    initscr();
    
    if(has_colors() == FALSE)
	{	endwin();
		printf("Your terminal does not support color\n");
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

    createWindow(m_rows, m_cols); // Create our root window
    m_mainWindow = m_windows.at(0); // Assign it here
    
    addToPanelList(m_mainWindow); // Add our window to the panel list manually
    update_panels();

    m_panels.at(0)->setName("Main Window");
    
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

    _SharedPtr<ncursesPanel> top = m_panels.at(0);

    wclear(top->getChild()->get());
    mvwprintw(top->getChild()->get(), 1, (m_cols - top->getName().size())/2, "%s", top->getName().c_str());
    top_panel(top->getPanel());
//    wrefresh(top->getChild()->get());
  //  refresh();

    m_panels.at(1)->setName("Navigation");
    GraphChart graphController(m_windows.at(1));
 //   graphController.fill();
 //   mvwprintw(m_panels.at(1)->getChild()->get(), 1, (m_cols - m_panels.at(1)->getName().size())/2, "%s", m_panels.at(1)->getName().c_str());
//    wrefresh(m_panels.at(1)->getChild()->get());
    
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

    
    int c;
    
    while(m_running)
	{
        wrefresh(top->getChild()->get());
        refresh();
        update_panels();
        doupdate();
        
        c = getch();//wgetch(m_mainWindow->get());
		switch(c)
		{

            case KEY_F(1):
                top = m_panels.at(1);
                wclear(top->getChild()->get());
                mvwprintw(top->getChild()->get(), 1, (m_cols - top->getName().size())/2, "%s", top->getName().c_str());
                top->getChild()->render();
                graphController.fill();
                top_panel(m_panels.at(1)->getPanel());
                break;
                
            case KEY_F(2):
                top = m_panels.at(2);
                mvwprintw(top->getChild()->get(), 1, (m_cols - top->getName().size())/2, "%s", top->getName().c_str());
                top->getChild()->render();
                top_panel(m_panels.at(2)->getPanel());
                break;
                
            case KEY_F(3):
                top = m_panels.at(0);
                wclear(top->getChild()->get());
                menuMain->render();
                top_panel(m_panels.at(0)->getPanel());
                break;
                
                // This is the TAB key
            case 9:
                top->getChild()->clearScreen();
                top->getChild()->render();
                top = top->getNext();
                mvwprintw(top->getChild()->get(), 1, (m_cols - top->getName().size())/2, "%s", top->getName().c_str());
                top_panel(top->getPanel());
				break;

            default:
                top->getChild()->clearScreen();
                top->getChild()->handleKeys(c);
                top->getChild()->render();
                break;

		}

        //refresh();
	}
    
    
    /*
     m_mainWindow = newwin(m_rows-2, m_cols-2, 0, 0);
     box(m_mainWindow, 0,0);
     wrefresh(m_mainWindow);
     attron(A_BOLD);
     std::string mes = "Press enter a command to continue";
     attroff(A_BOLD);
     mvwprintw(m_mainWindow, 2, 2, "%s", mes.c_str());
     mvwprintw(m_mainWindow, m_rows-2,0,"%s", "> ");
     */
    
    wrefresh(m_mainWindow->get());
    
    
    /*
    std::string input;
    char instring[80];
    getstr(instring); 
     */
    
    
    /*
    mvwprintw(m_mainWindow->get(), m_rows-2, 1, "The command entered is: ");
    attron(A_BOLD | A_BLINK);
    wprintw(m_mainWindow->get(), "%s", instring);
    attroff(A_BOLD | A_BLINK);
    wrefresh(m_mainWindow->get());
    getch();
    */
    return true;
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
        set_panel_userptr(m_panels.at(panelListSize-1)->getPanel(), m_panels.back()->getPanel());
        set_panel_userptr(m_panels.back()->getPanel(), m_panels.front()->getPanel());
        
        m_panels.at(panelListSize-1)->addNext(m_panels.back());
        m_panels.back()->addPrev(m_panels.at(panelListSize-1));
        m_panels.back()->addNext(m_panels.at(0));

    }

    update_panels();
    doupdate();


}


void Shell::createWindow(int ysize, int xsize){
    
    _SharedPtr<ncursesWindow> new_window = _SharedPtr<ncursesWindow>(new ncursesWindow(m_rows, m_cols, 0, 0)); // Initialize our root window
    m_windows.push_back(new_window); // Add to the list of Windows for the window manager.

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
