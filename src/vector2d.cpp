//
//  vector2d.cpp
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 9/3/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//

#include "vector2d.h"


Origin2D_ Origin2D;


Vector2D& Vector2D::Rotate(double angle)
{
    double s = sinf(angle);
    double c = cosf(angle);
    
    double nx = c * x - s * y;
    double ny = s * x + c * y;
    
    x = nx;
    y = ny;
    
    return (*this);
}
