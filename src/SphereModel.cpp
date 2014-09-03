//
//  SphereModel.cpp
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 9/2/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//

#include "SphereModel.h"
#include "logger.h"



SphereModel::SphereModel() : TRModel() {
        

    std::vector<Vector3D> m_spherePoints;
    m_mesh = _SharedPtr<MeshModel>(new MeshModel);

    int recursion = 2;
    initialize_sphere(m_spherePoints, recursion);  // where DEPTH should be the subdivision depth

    //logger logmaker("log.txt", 0);
    


    for(int x = 0; x < m_triangles.size(); x++){
        
        
            _SharedPtr<TerosPolygon> l_triangle = _SharedPtr<TerosPolygon>(new TerosPolygon);
            l_triangle->modp(0, m_spherePoints.at(m_triangles.at(x)->v1).x, m_spherePoints.at(m_triangles.at(x)->v1).y, m_spherePoints.at(m_triangles.at(x)->v1).z);
            l_triangle->modp(1, m_spherePoints.at(m_triangles.at(x)->v2).x, m_spherePoints.at(m_triangles.at(x)->v2).y, m_spherePoints.at(m_triangles.at(x)->v2).z);
            l_triangle->modp(2, m_spherePoints.at(m_triangles.at(x)->v3).x, m_spherePoints.at(m_triangles.at(x)->v3).y, m_spherePoints.at(m_triangles.at(x)->v3).z);

        if(x%2)
            l_triangle->setfill('#');
        else
            l_triangle->setfill('@');
            //l_triangle->settexturemode(false);
            m_buffer.push_back(l_triangle);

    }

    
    for(int x = 0; x < m_buffer.size(); x++){
        m_model->addside(m_buffer.at(x).get());
    }

    double center[3] = {0,0,0};
    m_model->center(center);
    m_model->ctrscaleoff(0, 0, 0);
    
}


int SphereModel::getMiddlePointID(int p1, int p2)
{
    return 0;

}




void SphereModel::initialize_sphere(std::vector<Vector3D> &sphere_points, const unsigned int depth) {

    
    auto icosaVertices = new Vector3D[12];
    
    double theta = 26.56505117707799 * PI / 180.0; // refer paper for theta value
    
    double stheta = std::sin(theta);
    double ctheta = std::cos(theta);
    
    icosaVertices[0] = Vector3D(0.0f, 0.0f, -1.0f); // the lower vertex
    
    // the lower pentagon
    double phi = PI / 5.0;
    for (int i = 1; i < 6; ++i) {
        icosaVertices[i] = Vector3D(ctheta * std::cos(phi), ctheta * std::sin(phi), -stheta).Normalize();
        
        phi += (2.0 * PI) / 5.0;
    }
    
    // the upper pentagon
    phi = 0.0;
    for (int i = 6; i < 11; ++i) {
        icosaVertices[i] = Vector3D(theta * std::cos(phi), ctheta * std::sin(phi), stheta).Normalize();
        
        phi += (2.0 * PI) / 5.0;
    }
    
    icosaVertices[11] = Vector3D(0.0f, 0.0f, 1.0f).Normalize(); // the upper vertex
    
    m_triangles.push_back(_SharedPtr<TriangleIndice>(new TriangleIndice(0, 2, 1)));
    m_triangles.push_back(_SharedPtr<TriangleIndice>(new TriangleIndice(0, 3, 2)));
    m_triangles.push_back(_SharedPtr<TriangleIndice>(new TriangleIndice(0, 4, 3)));
    m_triangles.push_back(_SharedPtr<TriangleIndice>(new TriangleIndice(0, 5, 4)));
    m_triangles.push_back(_SharedPtr<TriangleIndice>(new TriangleIndice(0, 1, 5)));
    
    m_triangles.push_back(_SharedPtr<TriangleIndice>(new TriangleIndice(1, 2, 7)));
    m_triangles.push_back(_SharedPtr<TriangleIndice>(new TriangleIndice(2, 3, 8)));
    m_triangles.push_back(_SharedPtr<TriangleIndice>(new TriangleIndice(3, 4, 9)));
    m_triangles.push_back(_SharedPtr<TriangleIndice>(new TriangleIndice(4, 5, 10)));
    m_triangles.push_back(_SharedPtr<TriangleIndice>(new TriangleIndice(5, 1, 6)));
    
    m_triangles.push_back(_SharedPtr<TriangleIndice>(new TriangleIndice(1, 7, 6)));
    m_triangles.push_back(_SharedPtr<TriangleIndice>(new TriangleIndice(2, 8, 7)));
    m_triangles.push_back(_SharedPtr<TriangleIndice>(new TriangleIndice(3, 9, 8)));
    m_triangles.push_back(_SharedPtr<TriangleIndice>(new TriangleIndice(4, 10, 9)));
    m_triangles.push_back(_SharedPtr<TriangleIndice>(new TriangleIndice(5, 6, 10)));
    
    m_triangles.push_back(_SharedPtr<TriangleIndice>(new TriangleIndice(6, 7, 11)));
    m_triangles.push_back(_SharedPtr<TriangleIndice>(new TriangleIndice(7, 8, 11)));
    m_triangles.push_back(_SharedPtr<TriangleIndice>(new TriangleIndice(8, 9, 11)));
    m_triangles.push_back(_SharedPtr<TriangleIndice>(new TriangleIndice(9, 10, 11)));
    m_triangles.push_back(_SharedPtr<TriangleIndice>(new TriangleIndice(10, 6, 11)));
    
    
    
    
    for(int i = 0; i < 12; i++){
        
        sphere_points.push_back(icosaVertices[i]);
        
    }

    for(int i = 0; i < 20; i++){
        
        subdivide(sphere_points.at(m_triangles.at(i)->v1), sphere_points.at(m_triangles.at(i)->v2), sphere_points.at(m_triangles.at(i)->v3), sphere_points, depth);
    }
    
}


void SphereModel::subdivide(const Vector3D &v1, const Vector3D &v2, const Vector3D &v3, vector<Vector3D> &sphere_points, const unsigned int depth) {
    
    if(depth == 0) {
        int index = sphere_points.size();
        sphere_points.push_back(v1);
        sphere_points.push_back(v2);
        sphere_points.push_back(v3);
        
        m_triangles.push_back(_SharedPtr<TriangleIndice>(new TriangleIndice(index, index+1, index+2)));

        return;
    }
    const Vector3D v12 = (v1 + v2).Normalize();
    const Vector3D v23 = (v2 + v3).Normalize();
    const Vector3D v31 = (v3 + v1).Normalize();
    subdivide(v1, v12, v31, sphere_points, depth - 1);
    subdivide(v2, v23, v12, sphere_points, depth - 1);
    subdivide(v3, v31, v23, sphere_points, depth - 1);
    subdivide(v12, v23, v31, sphere_points, depth - 1);
    
}


void SphereModel::constructFromMesh(_SharedPtr<MeshModel> model){

}



void SphereModel::subdivide(int depth) {
    
}




void SphereModel::move(double xdisp, double ydisp, double zdisp){
    
    
}


void SphereModel::rotate(char direction, double radians){
    
    
}


void SphereModel::reset(){
    
    
}





