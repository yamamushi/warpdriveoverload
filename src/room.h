//
//  room.h
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 8/19/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//

#ifndef __warpdriveoverloaded__room__
#define __warpdriveoverloaded__room__

#include <string>
#include <vector>
#include <memory>

#include "entity.h"
#include "tr1_wrapper.h"



class Room {
    
public:
    
    Room(int x, int y, int z) : m_x(x), m_y(y), m_z(z){};
    Room(){};

    
    void enterDescription(std::string description){m_description = description;}
    std::string getDescription();
    
    void addEntity(_SharedPtr<Entity> target);
    
    
private:
    
    // Dimensions in meters.
    int m_x;
    int m_y;
    int m_z;
    
    // Text Data
    
    std::string m_description;
    
    std::vector<_SharedPtr<Entity> > m_entities;
    
};


#endif /* defined(__warpdriveoverloaded__room__) */