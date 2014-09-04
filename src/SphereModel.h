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




struct MeshModel {
    
    std::vector<_SharedPtr<TriangleIndice> > m_indices;
    std::vector<Vector3D> m_points;
    
};

class SphereModel : public TRModel //Declaring a new class, derivative of the R3Object class, for our advanced 'TreasureChest' object.
{
    
public:
    
    SphereModel(); //Prototyping a constructor function for our TreasureChest class.
    
    void move(double xdisp, double ydisp, double zdisp);
    void rotate(char direction, double radians);
    void reset();
    
    
private:
    
    void initialize_sphere(std::vector<Vector3D> &sphere_points, const unsigned int depth);
    void subdivide(const Vector3D &v1, const Vector3D &v2, const Vector3D &v3, std::vector<Vector3D> &sphere_points, const unsigned int depth);
    void addVertex(Vector3D p);
    int getMiddlePoint(double p1, double p2);
    void constructFromMesh(_SharedPtr<MeshModel> mesh);
    void subdivide(int depth);
    int getMiddlePointID(int p1, int p2);

    
    _SharedPtr<MeshModel> m_mesh;
    std::vector<_SharedPtr<TerosPolygon> > m_buffer;
    
    std::vector<_SharedPtr<TriangleIndice> > m_triangles;
    std::vector<Vector3D> m_spherePoints;

};

#endif /* defined(__warpdriveoverloaded__SphereModel__) */
