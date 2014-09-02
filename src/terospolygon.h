//
//  terospolygon.h
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 9/1/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//

#ifndef __warpdriveoverloaded__terospolygon__
#define __warpdriveoverloaded__terospolygon__


class TerosPolygon
{
private:
    double xcoord [3];
    double ycoord [3];
    double zcoord [3];
    
    char fill;
    char transparency;
    
    bool texturemode;
    
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
};


#endif /* defined(__warpdriveoverloaded__terospolygon__) */
