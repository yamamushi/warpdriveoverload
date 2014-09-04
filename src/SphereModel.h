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
#include "terosR3.h"
#include "TRModel.h"
#include "vector2d.h"
#include "vector3d.h"

#include <vector>


class TRModel;

struct TriangleIndice
{
    int v1;
    int v2;
    int v3;
    
    TriangleIndice(int p1, int p2, int p3) : v1(p1), v2(p2), v3(p3) {};
};

struct Point3d{
    
    double p1;
    double p2;
    double p3;
    
    Point3d(double v1, double v2, double v3) : p1(v1), p2(v2), p3(v3) {};

};

struct MeshModel {
    
    //std::vector<_SharedPtr<TriangleIndices> > indices;
    std::vector<_SharedPtr<Vector3D> >         points;
    
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
    std::vector<Point3d> m_points;

};

#endif /* defined(__warpdriveoverloaded__SphereModel__) */
