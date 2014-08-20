//
//  room.cpp
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 8/19/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//

#include "room.h"
#include "term_control.h"


std::string Room::getDescription(){
    
    std::string output;
    
    output += m_description;
    output += "\n\n";
    output += "You see here: " + ascii_bold + ascii_red;
    
    for(int x = 0; x < m_entities.size(); x++){
        output += m_entities.at(x)->getName();
        if(x == m_entities.size() - 1){
            output += term_reset + ". ";
        }
        else{
            output += ", ";
        }
    }
    
    return output;
}

void Room::addEntity(std::shared_ptr<Entity> target){
    
    m_entities.push_back(target);
    
}


