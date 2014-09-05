//
//  SphereModel.cpp
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 9/2/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//

#include "SphereModel.h"
#include "logger.h"



SphereModel::SphereModel(int smoothness) : TRModel() {
    
    int recursion = smoothness;
    initialize_sphere(m_spherePoints, recursion);  // where DEPTH should be the subdivision depth


    // This prepares our mesh as m_model (TRObject)
    constructFromMesh();
/*    
    TerosPolygon intersect;
    int index = findIntersectIndex(1.0, 1.0, 5.0);
    intersect.modp(0, m_mesh->m_points.at(m_mesh->m_indices.at(index).x()).x(), m_mesh->m_points.at(m_mesh->m_indices.at(index).x()).y(), m_mesh->m_points.at(m_mesh->m_indices.at(index).x()).z());
    intersect.modp(1, m_mesh->m_points.at(m_mesh->m_indices.at(index).y()).x(), m_mesh->m_points.at(m_mesh->m_indices.at(index).y()).y(), m_mesh->m_points.at(m_mesh->m_indices.at(index).y()).z());
    intersect.modp(2, m_mesh->m_points.at(m_mesh->m_indices.at(index).z()).x(), m_mesh->m_points.at(m_mesh->m_indices.at(index).z()).y(), m_mesh->m_points.at(m_mesh->m_indices.at(index).z()).z());
    intersect.setfill('F');
    
    m_model->addside(&intersect);
    
  */  
    double center[3] = {0,0,0};
    m_model->center(center);
    m_model->ctrscaleoff(0, 0, 0);
    
}



void SphereModel::initialize_sphere(std::vector<Vector3D> &sphere_points, const unsigned int depth) {

    
    auto icosaVertices = new Vector3D[12];
    
    double theta = 26.56505117707799 * PI / 180.0; // refer paper for theta value
    
    double stheta = std::sin(theta);
    double ctheta = std::cos(theta);
    
    icosaVertices[0] = Vector3D(0.0, 0.0, -1.0); // the lower vertex
    
    // the lower pentagon
    double phi = PI / 5.0;
    for (int i = 1; i < 6; ++i) {
        icosaVertices[i] = Vector3D(ctheta * std::cos(phi), ctheta * std::sin(phi), -stheta);
        phi += (2.0 * PI) / 5.0;
    }
    
    // the upper pentagon
    phi = 0.0;
    for (int i = 6; i < 11; ++i) {
        icosaVertices[i] = Vector3D(theta * std::cos(phi), ctheta * std::sin(phi), stheta);
        phi += (2.0 * PI) / 5.0;
    }
    
    icosaVertices[11] = Vector3D(0.0, 0.0, 1.0);// the upper vertex
    
    m_mesh->m_indices.push_back(TriangleIndice(0, 2, 1));
    m_mesh->m_indices.push_back(TriangleIndice(0, 3, 2));
    m_mesh->m_indices.push_back(TriangleIndice(0, 4, 3));
    m_mesh->m_indices.push_back(TriangleIndice(0, 5, 4));
    m_mesh->m_indices.push_back(TriangleIndice(0, 1, 5));
    
    m_mesh->m_indices.push_back(TriangleIndice(1, 2, 7));
    m_mesh->m_indices.push_back(TriangleIndice(2, 3, 8));
    m_mesh->m_indices.push_back(TriangleIndice(3, 4, 9));
    m_mesh->m_indices.push_back(TriangleIndice(4, 5, 10));
    m_mesh->m_indices.push_back(TriangleIndice(5, 1, 6));
    
    m_mesh->m_indices.push_back(TriangleIndice(1, 7, 6));
    m_mesh->m_indices.push_back(TriangleIndice(2, 8, 7));
    m_mesh->m_indices.push_back(TriangleIndice(3, 9, 8));
    m_mesh->m_indices.push_back(TriangleIndice(4, 10, 9));
    m_mesh->m_indices.push_back(TriangleIndice(5, 6, 10));
    
    m_mesh->m_indices.push_back(TriangleIndice(6, 7, 11));
    m_mesh->m_indices.push_back(TriangleIndice(7, 8, 11));
    m_mesh->m_indices.push_back(TriangleIndice(8, 9, 11));
    m_mesh->m_indices.push_back(TriangleIndice(9, 10, 11));
    m_mesh->m_indices.push_back(TriangleIndice(10, 6, 11));
    
    
    for(int i = 0; i < 12; i++){
        
        m_mesh->m_points.push_back(icosaVertices[i]);
        
    }

    for(int i = 0; i < 20; i++){
        
        subdivide(m_mesh->m_points.at(m_mesh->m_indices.at(i).x()), m_mesh->m_points.at(m_mesh->m_indices.at(i).y()), m_mesh->m_points.at(m_mesh->m_indices.at(i).z()), m_mesh->m_points, depth);
        m_mesh->m_colors.push_back(ColorIndice(i, 'D', COLOR_YELLOW, COLOR_BLACK, 0));
    }
    
}


void SphereModel::subdivide(const Vector3D &v1, const Vector3D &v2, const Vector3D &v3, std::vector<Vector3D> &sphere_points, const unsigned int depth) {
    
    if(depth == 0) {
        int index = m_mesh->m_points.size();
        m_mesh->m_points.push_back(v1);
        m_mesh->m_points.push_back(v2);
        m_mesh->m_points.push_back(v3);

        m_mesh->m_colors.push_back(ColorIndice(index, '~', COLOR_BLUE, COLOR_BLACK));
        m_mesh->m_colors.push_back(ColorIndice(index+1, '^', COLOR_WHITE, COLOR_BLACK, 0));
	if(index%2)
        	m_mesh->m_colors.push_back(ColorIndice(index+2, '=', COLOR_GREEN, COLOR_BLACK, 0));
	else
               	m_mesh->m_colors.push_back(ColorIndice(index+2, '#', COLOR_GREEN, COLOR_BLACK, 0));
        m_mesh->m_colors.push_back(ColorIndice(index+3, 'M', COLOR_RED, COLOR_BLACK, 0));

        m_mesh->m_indices.push_back(TriangleIndice(index, index+1, index+2));

        return;
    }

    Vector3D v12 = Vector3D(v1 + v2);
    v12.normalize();
    Vector3D v23 = Vector3D(v2 + v3);
    v23.normalize();
    Vector3D v31 = Vector3D(v3 + v1);
    v31.normalize();
    
    subdivide(v1, v12, v31, sphere_points, depth - 1);
    subdivide(v2, v23, v12, sphere_points, depth - 1);
    subdivide(v3, v31, v23, sphere_points, depth - 1);
    subdivide(v12, v23, v31, sphere_points, depth - 1);
    
}



int SphereModel::findIntersectIndex(double x, double y, double length){
    
    logger logangle("log.txt", 0);
    
    int index = 0;
    
    vmml::vector<3, double> center(0,0,0);
    vmml::vector<3, double> direction(x,y,length);
    Vector3D intersect;

    for(int x = 0; x < m_mesh->m_indices.size(); x++){
        
        if(rayIntersectsTriangle( center, direction, m_mesh->m_points.at(m_mesh->m_indices.at(x).x()), m_mesh->m_points.at(m_mesh->m_indices.at(x).y()), m_mesh->m_points.at(m_mesh->m_indices.at(x).z()))){
         
            logangle.logToFile("Intersection at: " + std::to_string(x), 0);
            
            index = x;
        }
    }
    
    return index;
}


void SphereModel::move(double xdisp, double ydisp, double zdisp){
    
    
}


void SphereModel::rotate(char direction, double radians){
    
    
}


void SphereModel::reset(){
    
    

}





bool SphereModel::rayIntersectsTriangle(Vector3D point, Vector3D direction, Vector3D pt1, Vector3D pt2, Vector3D pt3) {
    
	//float e1[3],e2[3],h[3],s[3],q[3];
	float a,f,u,v, t;
	Vector3D e1 = pt2 - pt1;
	Vector3D e2 = pt3 - pt1;

    Vector3D h = direction.cross(e2);
	a = e1.dot(h);
    
	if (a > -0.00001 && a < 0.00001)
		return(false);
    
	f = 1/a;
    Vector3D s = point - pt1;
	u = f * (s.dot(h));
    
	if (u < 0.0 || u > 1.0)
		return(false);
    
	//crossProduct(q,s,e1);
    Vector3D q = s.cross(e1);
	v = f * direction.dot(q);
    
	if (v < 0.0 || u + v > 1.0)
		return(false);
    
	// at this stage we can compute t to find out where
	// the intersection point is on the line
	t = f * e2.dot(q);
    
	if (t > 0.00001) // ray intersection
		return(true);
    
	else // this means that there is a line intersection
        // but not a ray intersection
        return (false);
    
}


