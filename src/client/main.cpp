//
//  main.cpp
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 8/19/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include "db/sqlite.h"
#include "engine/game_engine.h"
#include "tr1/tr1_wrapper.h"
#include "engine/shell.h"
#include "util/term_control.h"
#include <locale.h>
#include "config.h"
#include "util/logger.h"


//#ifdef _WARPDRIVE_NCURSESCLIENT_

#ifdef __APPLE__
extern "C" int main(int argc, char **argv){
#else
    int main(int argc, char **argv){
#endif


    setlocale(LC_ALL, "en_US.UTF-8");

    term_clear();

    sqliteDB::instance()->run();

    //GlobalLogger::Instance()->writeToLogFile("debug.log", "Main");
    //GlobalLogger::Instance()->writeToLogFile("debug.log", "Started");

    _SharedPtr<Nostradamus> nostradamus(new Nostradamus);
    _SharedPtr<Shell>shell(new Shell(nostradamus));

    shell->boot();
    shell->loadInterfaces(shell);
    shell->run();

    while(shell->running()){

    }


    return 0;

}
