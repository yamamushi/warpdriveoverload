//
//  game_engine.h
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 8/19/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//

#ifndef __warpdriveoverloaded__game_engine__
#define __warpdriveoverloaded__game_engine__

#include "db/sqlite.h"
#include "game/room.h"
#include "tr1/tr1_wrapper.h"

#include <vector>
#include <string>


class Nostradamus {
    
public:
    
    Nostradamus();
    
    
private:
    
    void init();
    
    std::vector<_SharedPtr<Room> > m_rooms;
    
};



#endif /* defined(__warpdriveoverloaded__game_engine__) */
