//
//  TRModel.h
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 9/2/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//

#ifndef __warpdriveoverloaded__TRModel__
#define __warpdriveoverloaded__TRModel__

#include "tr1/tr1_wrapper.h"

#include "teros.h"
#include "terospolygon.h"
#include "terosobject.h"

#include <vector>
#include <cmath>
#include <string>

struct ColorIndice {
    
    int index;
    char s;
    int fg;
    int bg;
    int attr;
    
    ColorIndice(int i=-1, char symbol=' ', int fore=0, int back=0, int attribute=0) : index(i), s(symbol), fg(fore), bg(back), attr(attribute) {};

    
};

struct MeshModel {
    
    std::vector<_SharedPtr<TriangleIndice> > m_indices;
    std::vector<_SharedPtr<Vector3D> > m_points;
    std::vector<_SharedPtr<ColorIndice> > m_colors;
    
};


class TRModel
{

public:
    
    TRModel();
    
    virtual void move(double xdisp, double ydisp, double zdisp){};
    virtual void rotate(char direction, double radians){};
    virtual void reset(){};
    virtual _SharedPtr<TerosObject> getModel(){return m_model;}
    virtual void constructFromMesh(_SharedPtr<MeshModel> mesh, int size=1);
    virtual void constructFromMesh(){constructFromMesh(m_mesh);}
    virtual void constructFromMesh(int size){constructFromMesh(m_mesh, size);}

    
protected:
    
    // A container for the different pieces of our Model
    
    std::vector<_SharedPtr<TerosObject> > m_objectList;
    std::vector<_SharedPtr<TerosPolygon> > m_polygons;
    
    _SharedPtr<TerosObject> m_model;
    _SharedPtr<MeshModel> m_mesh;
    
    
    vmml::vector<4, double> m_position;
    vmml::vector<4, double> m_velocity;
    
    int m_posx, m_posy, m_posz;
    
};

#endif /* defined(__warpdriveoverloaded__TRModel__) */
