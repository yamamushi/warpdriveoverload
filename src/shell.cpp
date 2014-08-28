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
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    
    getmaxyx(stdscr,m_rows,m_cols);
    
    int startx;
    int starty;
    starty = 0;	/* Calculating for a center placement */
	startx = 0;	/* of the window		*/
    

    m_mainWindow = _SharedPtr<ncursesWindow>(new ncursesWindow(m_rows, m_cols, starty, startx));
    m_windows.push_back(m_mainWindow);
    wbkgd(m_mainWindow->get(), COLOR_PAIR(1));
    //box(m_mainWindow->get(), 0,0);
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

    int c;
    keypad(m_mainWindow->get(), TRUE);		/* We get F1, F2 etc..		*/

	//mvwprintw( m_mainWindow->get(), 1, 1, "F1 to Exit");
    wrefresh(m_mainWindow->get());

	refresh();
    
    GraphChart graphController(m_mainWindow);
    graphController.fill();
    

    while(1)
	{
        c = wgetch(m_mainWindow->get());
		switch(c)
		{
            case KEY_DOWN:
		        //menu_driver(my_menu, REQ_DOWN_ITEM);
				break;
			case KEY_UP:
				//menu_driver(my_menu, REQ_UP_ITEM);
                break;
            default:
                break;

		}
        //wrefresh(m_mainWindow->get());
        refresh();
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
    
    std::string input;
    char instring[80];
    getstr(instring);
    
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





void Shell::shutdown(){
    
    for(size_t x = 0; x < m_windows.size(); x++){
        m_windows.at(x)->close();
        
    }
    endwin();
    
}



void Shell::close_win(_SharedPtr<ncursesWindow> target_window){
    
    target_window->close();
    
    
}
