//
//  game_engine.cpp
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 8/19/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//

#include "game_engine.h"

#include <iostream>

Nostradamus::Nostradamus(){
        
    init();
    
}

void Nostradamus::init(){
    
    
    for(int x = 0; x < 10 ; x++){
        _SharedPtr<Room> l_room(new Room);
        l_room->enterDescription("Room: " + x);
        m_rooms.push_back(l_room);
    }
    
    std::cout << "Rooms Generated" << std::endl;
    
}
