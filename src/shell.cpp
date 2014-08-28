//
//  shell.cpp
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 8/28/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//

#include "shell.h"
#include "version.h"


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
    raw(); // disable line buffering
    keypad(stdscr, TRUE);		/* We get F1, F2 etc..		*/
    //noecho();			/* Don't echo() while we do getch */
    curs_set(0);
    int row, col;
    getmaxyx(stdscr,row,col);
    attron(A_BOLD);
    std::string mes = "Press enter a command to continue";
    attroff(A_BOLD);
    mvprintw(0, 0, "%s", mes.c_str());
    mvprintw(row-1,0,"%s", "> ");

    refresh();

    std::string input;
    char instring[80];
    getstr(instring);
    

        mvprintw(row-2, 0, "The command entered is: ");
		attron(A_BOLD | A_BLINK);
		printw("%s", instring);
		attroff(A_BOLD | A_BLINK);
    refresh();
    getch();
    
    return true;
}


void Shell::shutdown(){
    
    endwin();

}