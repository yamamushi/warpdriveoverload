//
//  vector3d.cpp
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 9/3/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//

#include "vector3d.h"


Origin3D_ Origin3D;


Vector3D& Vector3D::RotateAboutX(double angle)
{
    double s = sinf(angle);
    double c = cosf(angle);
    
    double ny = c * y - s * z;
    double nz = c * z + s * y;
    
    y = ny;
    z = nz;
    
    return (*this);
}

Vector3D& Vector3D::RotateAboutY(double angle)
{
    double s = sinf(angle);
    double c = cosf(angle);
    
    double nx = c * x + s * z;
    double nz = c * z - s * x;
    
    x = nx;
    z = nz;
    
    return (*this);
}

Vector3D& Vector3D::RotateAboutZ(double angle)
{
    double s = sinf(angle);
    double c = cosf(angle);
    
    double nx = c * x - s * y;
    double ny = c * y + s * x;
    
    x = nx;
    y = ny;
    
    return (*this);
}

Vector3D& Vector3D::RotateAboutAxis(double angle, const Vector3D& axis)
{
    double s = sinf(angle);
    double c = cosf(angle);
    double k = 1.0F - c;
    
    double nx = x * (c + k * axis.x * axis.x) + y * (k * axis.x * axis.y - s * axis.z)
    + z * (k * axis.x * axis.z + s * axis.y);
    double ny = x * (k * axis.x * axis.y + s * axis.z) + y * (c + k * axis.y * axis.y)
    + z * (k * axis.y * axis.z - s * axis.x);
    double nz = x * (k * axis.x * axis.z - s * axis.y) + y * (k * axis.y * axis.z + s * axis.x)
    + z * (c + k * axis.z * axis.z);
    
    x = nx;
    y = ny;
    z = nz;
    
    return (*this);
}
