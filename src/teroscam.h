#pragma once
/*
 
 A modified version of TEROS Engine 0.0.2.7 by Kyle L. Miskell - KyleMiskell@gmail.com
 
 Original TEROS project can be found at:
 
 https://github.com/SighoftheSecond/TEROS-ENGINE
 
 - Yamamushi
 
 */



#ifndef __warpdriveoverloaded__teroscam__
#define __warpdriveoverloaded__teroscam__

#include "teros.h"
#include "terospolygon.h"
#include "terosobject.h"

#include <string>
#include <vector>
#include <vmmlib/vector.hpp>
#include <vmmlib/matrix.hpp>


class TerosObject;

struct TerosView{
    
    char c;
    int fg;
    int bg;
    int attr;
    
};


class TerosCam
{
    
    
public:
    
    TerosCam ();
    
    void drawobjects ();
    void drawobject (TerosObject);
    void drawpolygon (TerosPolygon, TerosObject);
    void drawline (double [3], double [3], char fill, int fg=0, int bg=0, int attr=0);
    void setcampos (double, double, double);
    void addobject (TerosObject *);
    void delobject (int);
    void modobject (int, TerosObject *);
    void clearview ();
    void rotatecam (char, double);
    void basisreset ();
    void cpybasis (char, double [3]);
    void setviewsize (int, int);
    void modview (char, int, int);
    void modviewdepth (double, int, int);
    void texturepolygon (TerosPolygon, TerosObject);
    void applyrotation (double, double, double, double [3], double [3], TerosObject);
    void setzoomfactor (double);
    void scalept (double, double, double, double [3]);
    
    bool twodconvert (double [3], double [3], double [3], TerosObject, TerosPolygon);
    
    char getelement (int, int);
    char getelementraw (int);
    
    int getelementindex (int, int);
    int objectnum ();
    int putviewsize ();
    int putviewcolumns ();
    
    double getviewdepth (int, int);
    double getviewdepthraw (int);
    
    // Passing this a negative distance will result in moving backwards
    void moveForward( double speed, double distance);
    void moveRight( double speed, double distance);
    void moveUp( double speed, double distance);

    
    double putcamx ();
    double putcamy ();
    double putcamz ();
    
    vmml::vector<4, double> getAngleX();
    vmml::vector<4, double> getAngleY();
    vmml::vector<4, double> getAngleZ();
    
    double putzoomfactor ();
    
    std::vector<TerosView> putview ();
    std::vector<double> putviewdepth ();
    
    TerosObject * putobj (int);
    
    
private:
    
    std::vector<TerosView> view;
    std::vector<double> viewdepth;
    std::vector<TerosObject *> objects;
    
    double m_camx;
    double m_camy;
    double m_camz;
    double m_zoomfactor;
    
    double cambasisx [3];
    double cambasisy [3];
    double cambasisz [3];
    
    vmml::vector<4, double> m_position;
    vmml::matrix<4, 4, double> viewMatrix;
    void setViewMatrix();
    
    int m_viewcolumns;
    double m_speed;
    

    
};


#endif /* defined(__warpdriveoverloaded__teroscam__) */
