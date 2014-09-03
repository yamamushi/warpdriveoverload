//
//  TRModel.h
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 9/2/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//

#ifndef __warpdriveoverloaded__TRModel__
#define __warpdriveoverloaded__TRModel__

#include "tr1_wrapper.h"

#include "teros.h"
#include "terospolygon.h"
#include "terosR3.h"

#include <vector>
#include <cmath>


class TRModel //Declaring a new class, derivative of the R3Object class, for our advanced 'TreasureChest' object.
{

public:
    
    TRModel(){ m_model = _SharedPtr<TerosR3Object>(new TerosR3Object);}; //Prototyping a constructor function for our TreasureChest class.
    
    virtual void move(double xdisp, double ydisp, double zdisp){};
    virtual void rotate(char direction, double radians){};
    virtual void reset(){};
    virtual _SharedPtr<TerosR3Object> getModel(){return m_model;}
    
protected:
    
    // A container for the different pieces of our Model
    std::vector<_SharedPtr<TerosR3Object> > m_objectList;
    
    std::vector<_SharedPtr<TerosPolygon> > m_buffer; //Declaring a vector of Polygons to temporarily hold the instantaneous, transformed lid polygons.
    _SharedPtr<TerosR3Object> m_model;
};

#endif /* defined(__warpdriveoverloaded__TRModel__) */