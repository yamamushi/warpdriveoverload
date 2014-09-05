#pragma once
//
//  SphereModel.h
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 9/2/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//

#ifndef __warpdriveoverloaded__SphereModel__
#define __warpdriveoverloaded__SphereModel__

#include "tr1_wrapper.h"

#include "teros.h"
#include "terospolygon.h"
#include "TRModel.h"

#include <vector>

class TRModel;



class SphereModel : public TRModel //Declaring a new class, derivative of the R3Object class, for our advanced 'TreasureChest' object.
{
    
public:
    
    SphereModel(int smoothness=1); //Prototyping a constructor function for our TreasureChest class.
    
    void move(double xdisp, double ydisp, double zdisp);
    void rotate(char direction, double radians);
    void reset();
    
    int findIntersectIndex(double x, double y, double length);
    
    bool rayIntersectsTriangle(Vector3D point, Vector3D direction, Vector3D pt1, Vector3D pt2, Vector3D pt3);
    
private:
    
    void initialize_sphere(std::vector<Vector3D> &sphere_points, const unsigned int depth);
    void subdivide(const Vector3D &v1, const Vector3D &v2, const Vector3D &v3, std::vector<Vector3D> &sphere_points, const unsigned int depth);
    
    std::vector<Vector3D> m_spherePoints;

};

#endif /* defined(__warpdriveoverloaded__SphereModel__) */
