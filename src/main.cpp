//
//  main.cpp
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 8/19/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include "sqlite.h"
#include "game_engine.h"
#include "tr1_wrapper.h"
#include "shell.h"

int main(int argc, char **argv){
    
    term_clear();

    
    sqliteDB::instance()->run();
    
    _SharedPtr<Nostradamus> nostradamus(new Nostradamus);
    _SharedPtr<Shell>shell(new Shell(nostradamus));

    shell->boot();
    shell->loadInterfaces(shell);
    shell->run();
    
    while(shell->running()){
    
    }
    
    return 0;
    
}
