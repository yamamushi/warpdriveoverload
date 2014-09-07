/*
 
 A modified version of TEROS Engine 0.0.2.7 by Kyle L. Miskell - KyleMiskell@gmail.com
 
 Original TEROS project can be found at:
 
 https://github.com/SighoftheSecond/TEROS-ENGINE
 
 - Yamamushi
 
 */

#ifndef __warpdriveoverloaded__terospolygon__
#define __warpdriveoverloaded__terospolygon__

#include <vmmlib/vector.hpp>
#include <vmmlib/matrix.hpp>

#include <vector>
#include <string>

#include "tr1_wrapper.h"        

typedef vmml::vector<3, int> TriangleIndice;
typedef vmml::vector<3, double> Point3d;
typedef vmml::vector<3, double> Vector3D;

class TerosPolygon
{

public:
    
    TerosPolygon();
    
    void modp (int, double, double, double);
    void setfill (char);
    void settranspid (char);
    void center (double [3]);
    void putxyz (int, double [3]);
    void settexturemode (bool);
    
    bool puttexturemode ();
    
    char putfill ();
    char puttranspid ();
    
    double centerx ();
    double centery ();
    double centerz ();
    double putpx (int);
    double putpy (int);
    double putpz (int);
    
    void setAttr(char symbol=' ', int fg=0, int bg=0, int attr=0){fill=symbol; m_fg=fg; m_bg=bg; m_attr=attr;}
    int getfg(){return m_fg;}
    int getbg(){return m_bg;}
    int getattr(){return m_attr;}

    
    //_SharedPtr<PolygonAttribute> getAttr(){return m_attr;}
    
    void setIndex(int index){m_index = index;}
    int getIndex(){return m_index;}
    
private:
    
    double xcoord [3];
    double ycoord [3];
    double zcoord [3];
    
    char fill;
    char transparency;
    
    int m_index;
    
    bool texturemode;
    
    int m_fg;
    int m_bg;
    int m_attr;
    
};


#endif /* defined(__warpdriveoverloaded__terospolygon__) */
