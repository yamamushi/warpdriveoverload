#pragma once
/*
 
 A modified version of TEROS Engine 0.0.2.7 by Kyle L. Miskell - KyleMiskell@gmail.com
 
 Original TEROS project can be found at:
 
 https://github.com/SighoftheSecond/TEROS-ENGINE
 
 - Yamamushi
 
 */

#ifndef __warpdriveoverloaded__terosR3__
#define __warpdriveoverloaded__terosR3__

#include "teros.h"
#include "terospolygon.h"

#include <string>
#include <vector>

class TerosR3Object
{
private:
    std::vector<TerosPolygon *> sides;
    std::vector<TerosR3Object *> olink;
    std::vector<TerosR3Object *> rzlink;
    std::vector<TerosR3Object *> rxlink;
    std::vector<TerosR3Object *> rylink;
    std::vector<TerosPolygon> loadsides;
    
    double xbasis [3];
    double ybasis [3];
    double zbasis [3];
    double scalep [3];
    
    bool ctrscale;
    
public:
    TerosR3Object ();
    
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
    void addolink (TerosR3Object *, bool);
    void addrzlink (TerosR3Object *, bool);
    void addrxlink (TerosR3Object *, bool);
    void addrylink (TerosR3Object *, bool);
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
    
    TerosR3Object * putolink (int);
    TerosR3Object * putrzlink (int);
    TerosR3Object * putrxlink (int);
    TerosR3Object * putrylink (int);
    
    TerosPolygon putloadside (int);
    
    std::vector<TerosPolygon> permcpy ();
};

class TerosR3Cam
{
private:
    std::vector<char> view;
    std::vector<double> viewdepth;
    std::vector<TerosR3Object *> objects;
    
    double camx;
    double camy;
    double camz;
    double zoomfactor;
    
    double cambasisx [3];
    double cambasisy [3];
    double cambasisz [3];
    
    int viewcolumns;
    
public:
    TerosR3Cam ();
    
    void drawobjects ();
    void drawobject (TerosR3Object);
    void drawpolygon (TerosPolygon, TerosR3Object);
    void drawline (double [3], double [3], char);
    void setcampos (double, double, double);
    void addobject (TerosR3Object *);
    void delobject (int);
    void modobject (int, TerosR3Object *);
    void clearview ();
    void rotatecam (char, double);
    void basisreset ();
    void cpybasis (char, double [3]);
    void setviewsize (int, int);
    void modview (char, int, int);
    void modviewdepth (double, int, int);
    void texturepolygon (TerosPolygon, TerosR3Object);
    void applyrotation (double, double, double, double [3], double [3], TerosR3Object);
    void setzoomfactor (double);
    void scalept (double, double, double, double [3]);
    
    bool twodconvert (double [3], double [3], double [3], TerosR3Object, TerosPolygon);
    
    char getelement (int, int);
    char getelementraw (int);
    
    int getelementindex (int, int);
    int objectnum ();
    int putviewsize ();
    int putviewcolumns ();
    
    double getviewdepth (int, int);
    double getviewdepthraw (int);
    double putcamx ();
    double putcamy ();
    double putcamz ();
    double putzoomfactor ();
    
    std::vector<char> putview ();
    std::vector<double> putviewdepth ();
    
    TerosR3Object * putobj (int);
};

#endif /* defined(__warpdriveoverloaded__terosR3__) */
