#pragma once
/*
 
 A modified version of TEROS Engine 0.0.2.7 by Kyle L. Miskell - KyleMiskell@gmail.com
 
 Original TEROS project can be found at:
 
 https://github.com/SighoftheSecond/TEROS-ENGINE
 
 - Yamamushi
 
 */


#ifndef __warpdriveoverloaded__terosobject__
#define __warpdriveoverloaded__terosobject__

#include "teros.h"
#include "terospolygon.h"

#include <string>
#include <vector>
#include <vmmlib/vector.hpp>
#include <vmmlib/matrix.hpp>

class TerosObject
{
private:
    std::vector<TerosPolygon *> sides;
    std::vector<TerosObject *> olink;
    std::vector<TerosObject *> rzlink;
    std::vector<TerosObject *> rxlink;
    std::vector<TerosObject *> rylink;
    std::vector<TerosPolygon> loadsides;
    
    double xbasis [3];
    double ybasis [3];
    double zbasis [3];
    double scalep [3];
    
    std::vector<_SharedPtr<Vector3D> > m_points;
    
    bool ctrscale;
    
public:
    TerosObject ();
    
    void addside (TerosPolygon *);
    void delside (int);
    void modside (int, TerosPolygon *);
    void rref3x4 (double [3][4]);
    void rot (char, double);
    void basisreset ();
    void putbasis (char, double [3]);
    void modbasis (char, double [3]);
    void shiftctr (double, double, double);
    void setctr (double, double, double);
    void center (double [3]);
    void ctrscaleoff (double, double, double);
    void ctrscaleon ();
    void cpyscalep (double [3]);
    void addolink (TerosObject *, bool);
    void addrzlink (TerosObject *, bool);
    void addrxlink (TerosObject *, bool);
    void addrylink (TerosObject *, bool);
    void delolink (int, bool);
    void delrzlink (int, bool);
    void delrxlink (int, bool);
    void delrylink (int, bool);
    void setutexturemode (bool);
    void saveobj (std::string);
    void clrloadsides ();
    
    bool putctrscale ();
    
    int sidenum ();
    int olinknum ();
    int rzlinknum ();
    int rxlinknum ();
    int rylinknum ();
    int loadobj (std::string);
    int loadsidenum ();
    
    double centerx ();
    double centery ();
    double centerz ();
    
    TerosPolygon * putside (int);
    
    TerosObject * putolink (int);
    TerosObject * putrzlink (int);
    TerosObject * putrxlink (int);
    TerosObject * putrylink (int);
    
    TerosPolygon putloadside (int);
    
    std::vector<TerosPolygon> permcpy ();
};



#endif /* defined(__warpdriveoverloaded__terosobject__) */
