//
//  terosTerosPolygon.cpp
//  warpdriveoverloaded
//
//  Created by Jonathan Rumion on 9/1/14.
//  Copyright (c) 2014 TAP. All rights reserved.
//

#include "terospolygon.h"


TerosPolygon::TerosPolygon()
{
	texturemode = true;
    
	fill = '#';
	transparency = '`';
    
	xcoord [0] = 0;
	xcoord [1] = 0;
	xcoord [2] = 0;
    
	ycoord [0] = 0;
	ycoord [1] = 0;
	ycoord [2] = 0;
    
	zcoord [0] = 0;
	zcoord [1] = 0;
	zcoord [2] = 0;
}

void TerosPolygon::modp (int index, double x, double y, double z)
{
	if (index < 3 && index >= 0)
	{
		xcoord [index] = x;
        
		ycoord [index] = y;
        
		zcoord [index] = z;
	}
}

void TerosPolygon::setfill (char filler)
{
	fill = filler;
}

void TerosPolygon::settranspid (char trans)
{
	transparency = trans;
}

void TerosPolygon::center (double ctr [3])
{
	ctr [0] = centerx ();
	ctr [1] = centery ();
	ctr [2] = centerz ();
}

void TerosPolygon::putxyz (int index, double xyz [3])
{
	if (index >= 0 && index < 3)
	{
		xyz [0] = xcoord [index];
		xyz [1] = ycoord [index];
		xyz [2] = zcoord [index];
	}
}

void TerosPolygon::settexturemode (bool mode)
{
	texturemode = mode;
}

bool TerosPolygon::puttexturemode ()
{
	return texturemode;
}

char TerosPolygon::puttranspid ()
{
	return transparency;
}

char TerosPolygon::putfill ()
{
	return fill;
}

double TerosPolygon::centerx ()
{
	return (xcoord [0] + xcoord [1] + xcoord [2])/3.0;
}

double TerosPolygon::centery ()
{
	return (ycoord [0] + ycoord [1] + ycoord [2])/3.0;
}

double TerosPolygon::centerz ()
{
	return (zcoord [0] + zcoord [1] + zcoord [2])/3.0;
}

double TerosPolygon::putpx (int index)
{
	if (index < 3 && index >= 0)
	{
		return xcoord [index];
	}
    
	return 0;
}

double TerosPolygon::putpy (int index)
{
	if (index < 3 && index >= 0)
	{
		return ycoord [index];
	}
    
	return 0;
}

double TerosPolygon::putpz (int index)
{
	if (index < 3 && index >= 0)
	{
		return zcoord [index];
	}
    
	return 0;
}
